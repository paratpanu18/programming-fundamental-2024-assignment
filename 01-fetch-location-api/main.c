#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_LINE_LENGTH 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

const char APIBaseURL[] = "https://nominatim.openstreetmap.org/reverse?format=json&lat=%f&lon=%f";

char* ComposeAPIURL(float lat, float lon) {
    char* url = (char*)malloc(500 * sizeof(char));
    if (url != NULL) {
        sprintf(url, APIBaseURL, lat, lon);
        return url;
    }
    return NULL;
}

struct Location {
    char no[50];
    float lat;
    float lon;
    char place[100];
};

struct MemoryStruct {
    char* memory;
    size_t size;
};

// Callback function to write data fetched from cURL to a memory buffer
size_t WriteToMemory(void* contents, size_t size, size_t nmemb, struct MemoryStruct* mem) {
    size_t total_size = size * nmemb;
    char* ptr = (char*) realloc(mem->memory, mem->size + total_size + 1);
    if (ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, total_size);
    mem->size += total_size;
    mem->memory[mem->size] = 0;
    return total_size;
}

int main() {
    FILE* input;
    input = fopen("latlonfile.csv", "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    FILE* output;
    output = fopen("output.csv", "a");

    fprintf(output, "no,lat,long,place\n");

    char column[MAX_LINE_LENGTH];

    // Read and skip header
    if (fgets(column, MAX_LINE_LENGTH, input)) {
        printf("Header: %s", column);
    }

    CURL* curl = curl_easy_init();
    CURLcode res;

    if (curl) {
        while (fgets(column, MAX_LINE_LENGTH, input)) {
            struct Location location;

            char* token = strtok(column, ",");
            strcpy(location.no, token);

            token = strtok(NULL, ",");
            location.lat = atof(token);

            token = strtok(NULL, ",");
            location.lon = atof(token);

            char* api_url = ComposeAPIURL(location.lat, location.lon);
            if (api_url != NULL) {
                printf("Fetching data from: lat=%f, lon=%f\n", location.lat, location.lon);

                struct MemoryStruct chunk;
                chunk.memory = (char *) malloc(1);  // initial allocation
                chunk.size = 0;                     // no data at this point

                curl_easy_setopt(curl, CURLOPT_URL, api_url);
                curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36");
                curl_easy_setopt(curl, CURLOPT_REFERER, "https://www.google.com");
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteToMemory);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

                // Perform the cURL request
                res = curl_easy_perform(curl);

                if (res != CURLE_OK) {
                    fprintf(stderr, "Failed to fetch API for location %s: %s\n", location.no, curl_easy_strerror(res));
                }
                
                cJSON* json = cJSON_Parse(chunk.memory);
                if (json == NULL) {
                    printf("Faild to parse JSON");
                }
                else {
                    cJSON* display_name = cJSON_GetObjectItemCaseSensitive(json, "display_name");
                    if (cJSON_IsString(display_name)) {

                        char lat_str[50];
                        char lon_str[50];

                        sprintf(lat_str, "%.6f", location.lat);
                        sprintf(lon_str, "%.6f", location.lon);

                        // Escape double quotes in the display name
                        char display_name_escaped[MAX_LINE_LENGTH];
                        snprintf(display_name_escaped, sizeof(display_name_escaped), "\"%s\"", display_name->valuestring);

                        // Write to CSV file
                        fprintf(output, "%s,%s,%s,%s\n", location.no, lat_str, lon_str, display_name_escaped);
                    }
                    // Free the JSON object
                    cJSON_Delete(json);
                }

                // printf("%s", chunk.memory);

                free(api_url);
                free(chunk.memory);
            }
        }

        curl_easy_cleanup(curl);
    }

    // Close files
    fclose(input);

    return 0;
}
