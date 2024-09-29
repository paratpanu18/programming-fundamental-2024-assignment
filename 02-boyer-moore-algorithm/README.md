# Boyer-Moore Algorithm
ให้ใช้ Text File ตัวอย่าง [boyer-moore.txt](boyer-moore.txt) เป็นชุดข้อมูลสำหรับการค้นหา แล้วให้สร้างฟังก์ชัน `boyer_moore(text, data)` ซึ่งเป็นฟังก์ชันสำหรับการค้นหา `text` ใน `data` และให้เขียนโปรแกรมรับ Keyword ที่ใช้ในการค้นหา แล้วเรียกฟังก์ชัน `boyer_moore` ที่สร้างขึ้น แล้วแสดงผลตำแหน่งทั้งหมดที่พบ Keyword ใน Data

```c
int* boyer_moore(char* text, char* data) {
    int* result = (int*) malloc(MAX_INDICE * sizeof(int))
    
    // Your code here

    return result
}
```

## Example
```c
char text[] = "THIS IS A TEST TEXT";
char data[] = "TEST";

boyer_moore(text, data);
>> Pattern found at index 10
```

```c
char text[] = "AABAACAADAABAABA";
char data[] = "AABA";

boyer_moore(text, data);
>> Pattern found at index 0, 9, 12
```

> Example testcases are from [Boyer Moore Algorithm for Pattern Searching](https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/)

