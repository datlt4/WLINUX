import base64
import os
import sys
from glob import glob

import hashlib
from Crypto import Random
from Crypto.Cipher import AES


def aes_encrypt(key, raw): # raw in str
    bs = AES.block_size
    raw = raw + (bs - len(raw) % bs) * chr(bs - len(raw) % bs)
    iv = Random.new().read(bs)
    key = hashlib.sha256(key.encode()).digest()
    cipher = AES.new(key, AES.MODE_CBC, iv)
    return base64.b64encode(iv + cipher.encrypt(raw.encode()))

def aes_decrypt(key, enc): # enc in bytes
    enc = base64.b64decode(enc)
    iv = enc[:AES.block_size]
    key = hashlib.sha256(key.encode()).digest()
    cipher = AES.new(key, AES.MODE_CBC, iv)
    s = cipher.decrypt(enc[AES.block_size:])
    return s[:-ord(s[len(s)-1:])]#.decode('utf-8')


if __name__ == "__main__":
    os.system("cat /proc/device-tree/serial-number >> serial_number")
    with open("serial_number", mode="rb") as f:
        device_serial_number = f.read()

    os.system("rm -f serial_number")

    if not glob(".unique"):
        base64_encoded_serial_number = base64.b64encode(device_serial_number)
        base64_serial_number = base64_encoded_serial_number.decode("utf-8")
        with open(".unique", mode="wb") as f:
            aes_serial_number = aes_encrypt("HUST", base64_serial_number)
            f.write(aes_serial_number)
    else:
        with open(".unique", mode="rb") as f:
            aes_serial_number = f.read()
            base64_serial_number = aes_decrypt("HUST", aes_serial_number)
            my_serial_number = base64.decodebytes(base64_serial_number)
        if not my_serial_number == device_serial_number:
            sys.exit("Serial numbers is not identical")

    print("Xuân đang qua lại một năm nữa")
    print("Bao lâu chưa được cầm tay ai")
    print("Nhìn người ta có đôi có cặp")
    print("Còn riêng tôi đã bao mùa trăng với cô đơn")
    print("Anh không mong gì nhiều hơn có em babe")
    print("Muốn nắm lấy tay em bước qua")
    print("muôn ngàn hoa với muôn ngàn sao")
    print("Ngước lên trên trời cao")
    print("Là trái tim thật to anh vẽ lên trên bầu trời")
    print("Yêu em, là anh sẽ yêu lâu dài")
    print("Bảo vệ em trước bão giông")
    print("Vượt hư không thời gian mình vẫn sống dai")
    print("Trong giấc mơ tình thăng hoa")
    print("Cùng em đến nơi an toàn")
    print("Còn riêng anh sẽ nguyện mãi ngoan bên đời em")
    print("Xin hãy đến đây xua tan hết cô đơn đời anh")
    print("Xuân đang qua niềm vui phơi phới")
    print("Đôi uyên ương cùng khoe áo mới")
    print("Tình nhân hôn mỗi khi xuân về")
    print("Còn riêng anh trốn sau hàng cây với cô đơn")
    print("Anh không mong gì nhiều hơn có em babe")
    print("Muốn nắm lấy tay em bước qua")
    print("Muôn ngàn hoa với muôn ngàn sao")
    print("Ngước lên trên trời cao")
    print("Thùng thính to thật to anh muốn quăng lên bầu trời")
    print("Yêu em, là anh sẽ yêu lâu dài")
    print("Bảo vệ em trước bão giông")
    print("Vượt hư không thời gian mình vẫn sống dai")
    print("Trong giấc mơ tình thăng hoa")
    print("Cùng em đến nơi an toàn")
    print("Còn riêng anh nguyện mãi ngoan bên đời em")
    print("Xin hãy đến đây xua tan hết cô đơn đời anh")
    print("Yêu em, là anh sẽ yêu lâu dài")
    print("Bảo vệ em trước bão giông")
    print("Vượt hư không thời gian mà mình vẫn sống dai")
    print("Yêu em, là anh sẽ yêu lâu dài")
    print("Bảo vệ em trước bão giông")
    print("Vượt hư không thời gian mà mình vẫn sống dai")
    print("Trong giấc mơ tình thăng hoa")
    print("Cùng em đến nơi an toàn")
    print("Còn riêng anh nguyện mãi ngoan bên đời em")
    print("Xin hãy đến đây xua tan hết cô đơn đời anh")
    print("Còn riêng anh nguyện mãi ngoan bên đời em")
    print("xin hãy đến đây xua tan hết cô đơn đời anh")

