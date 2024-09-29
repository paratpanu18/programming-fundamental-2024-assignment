# Location API Fetching
ให้ใช้ CSV (comma-separated value) file ตัวอย่าง [latlonfile.csv](latlonfile.csv) แล้วเขียนโปรแกรมอ่านไฟล์ดังกล่าว โดยนำค่า lat,lon แต่ละค่าไป query หาค่าสถานที่โดยใช้ URL ที่กำหนด หลังจากนั้น สร้าง CSV file ใหม่ โดยเพิ่มข้อมูลสถานที่ต่อท้ายแต่ละบรรทัด โดยไฟล์ผลลัพธ์มีข้อมูล 4 ค่า คือ
- no
- lat
- lon
- place

URL ที่ใช้สำหรับค้นหาสถานที่จากพิกัด lat,lon คือ
```url
https://nominatim.openstreetmap.org/reverse?format=json&lat=13.690092&lon=100.750240
```

ตัวอย่าง Output:
```json
{
  "place_id": 252567029,
  "licence": "Data © OpenStreetMap contributors, ODbL 1.0. http://osm.org/copyright",
  "osm_type": "way",
  "osm_id": 388569476,
  "lat": "13.688824499999999",
  "lon": "100.74666864195521",
  "class": "aeroway",
  "type": "apron",
  "place_rank": 30,
  "importance": 0.000009999999999954,
  "addresstype": "aeroway",
  "name": "",
  "display_name": "ลู่ปั่นจักรยานเจริญสุขมงคลจิต ลู่ปั่นฟ้า, Ban Khlong Lat Krabang, Nong Prue Subdistrict, Nong Prue Subdistrict Administrative Organization, Bang Phli District, Samut Prakan Province, Thailand",
  "address": {
    "road": "ลู่ปั่นจักรยานเจริญสุขมงคลจิต ลู่ปั่นฟ้า",
    "village": "Ban Khlong Lat Krabang",
    "city": "Nong Prue Subdistrict",
    "county": "Nong Prue Subdistrict Administrative Organization",
    "province": "Samut Prakan Province",
    "ISO3166-2-lvl4": "TH-11",
    "country": "Thailand",
    "country_code": "th"
  },
  "boundingbox": [
    "13.6863162",
    "13.6918201",
    "100.7460479",
    "100.7535125"
  ]
}
```