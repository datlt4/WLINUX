# Chapter 2: Hosting programming : fundamental data structures.

## Primitive data types

- Redefinition of correspoding C / C++ types

|Scalar data type|Bit width|Purpose|
|:---:|:---:|---|
|`cl_char`|8|Signed two’s complement integer|
|`cl_uchar`|8|Unsigned two’s complement integer|
|`cl_short`|16|Signed two’s complement integer|
|`cl_ushort`|16|Unsigned two’s complement integer|
|`cl_int`|32|Signed two’s complement integer|
|`cl_uint`|32|Unsigned two’s complement integer|
|`cl_long`|64|Signed two’s complement integer|
|`cl_ulong`|64|Unsigned two’s complement integer|
|`cl_half`|16|Half-precision floating-point value|
|`cl_float`|32|Single-precision floating-point value|
|`cl_double`|64|Double-precision floating-point value|

## Accessing platforms

### Creating platform structures

- Từng platform là một structure biểu diễn một OpenCL implementation được cài đặt trên host.

- __Working with platform__ là một quá trình gồm 2 bước:
  - __Step 1:__ allocated for one or more `cl_platform_id`.
  - __Step 2:__ call `clGetPlatformIDs` để khởi tạo structures

- Hàm khởi tạo Platform.
```C++
cl_int clGetPlatformIDs(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms)
```
where:
> `platforms`: tham chiếu của biến structure kiểu `cl_platform_id`.<br>
> `num_entries`: (`>0`) số lượng platform ta muốn detect. (số lượng tối đa `cl_platform_id` được thêm vào mảng `platform`).<br>
> `num_platforms`: số lượng platform mà host phát hiện ra trong quá trình hoạt động của nó.<br>
> `return`: `0` - indicates success, `<0` - indicates failure.

- `platforms` và `num_platforms` có thể được set bằng `NULL`. Thường sử dụng trong trường hợp: đầu tiên sẽ tìm "how many platforms are installed" (`platforms = NULL` và `num_platforms` sẽ lưu số platforms đã được cài đặt). Sau đó khởi tạo tất cả các platforms (`num_platforms = NULL`).

<details>
  <summary>The following code shows how this is accomplished!</summary>

```Cpp
cl_platform_id *platforms;
cl_uint num_platforms;

clGetPlatformIDs(5, NULL, &num_platforms);

platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);

clGetPlatformIDs(num_platforms, platforms, NULL);
```

</details>

<a name="obtaining_platform_information"></a>
### Obtaining platform information

- Muốn lấy một số thông tin ngoài luồng của các platforms (OpenCL version, vendor...) gọi hàm `clGetPlatformInfo`.

```C++
cl_int clGetPlatformInfo(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
```

where:
> `platform`<br>
> `param_name`: loại thông tin đang muốn tìm kiếm.<br>
> `param_value_size`: bao nhiêu ký tự muốn lưu lại.<br>
> `param_value`: chuỗi `char` trả về.<br>
> `param_value_size_ret`: kích thước chuỗi trả về.

|Parameter name|Purpose|
|:---:|---|
|`CL_PLATFORM_NAME`|Returns the name associated with the platform|
|`CL_PLATFORM_VENDOR`|Identifies the vendor associated with the platform|
|`CL_PLATFORM_VERSION`|Returns the maximum version of OpenCL supported by the platform|
|`CL_PLATFORM_PROFILE`|Identifies whether the platform supports the full OpenCL standard (`FULL_PROFILE`) or the embedded standard (`EMBEDDED_PROFILE`)|
|`CL_PLATFORM_EXTENSIONS`|Returns a list of extensions supported by the platform|

<details>
  <summary>The following code shows how this is accomplished!</summary>

```Cpp
char pform_vendor[40];
clGetPlatformInfo(platforms[0], CL_PLATFORM_VENDOR, sizeof(pform_vendor), &pform_vendor, NULL);
```

</details>

<details>
  <summary>EXAMPLE CODE!</summary>

`platform_ext_test.c`

```C++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MAC
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

int main() {

   /* Host data structures */
   cl_platform_id *platforms;
   cl_uint num_platforms;
   cl_int i, err, platform_index = -1;

   /* Extension data */
   char* ext_data;							
   size_t ext_size;
   const char icd_ext[] = "cl_khr_icd";

   /* Find number of platforms */
   err = clGetPlatformIDs(1, NULL, &num_platforms);		
   if(err < 0) {		
      perror("Couldn't find any platforms.");			
      exit(1);							
   }									

   /* Access all installed platforms */
   platforms = (cl_platform_id*) 					
      malloc(sizeof(cl_platform_id) * num_platforms);		
   clGetPlatformIDs(num_platforms, platforms, NULL);		

   /* Find extensions of all platforms */
   for(i=0; i<num_platforms; i++) {

      /* Find size of extension data */
      err = clGetPlatformInfo(platforms[i], 			
         CL_PLATFORM_EXTENSIONS, 0, NULL, &ext_size);		
      if(err < 0) {
         perror("Couldn't read extension data.");			
         exit(1);
      }								

      /* Access extension data */
      ext_data = (char*)malloc(ext_size);				
      clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 	
            ext_size, ext_data, NULL);				
      printf("Platform %d supports extensions: %s\n", i, ext_data);

      /* Look for ICD extension */
      if(strstr(ext_data, icd_ext) != NULL) {
         free(ext_data);
         platform_index = i;
         break;
      }
      free(ext_data);
   }

   /* Display whether ICD extension is supported */
   if(platform_index > -1)
      printf("Platform %d supports the %s extension.\n",
            platform_index, icd_ext);
   else
      printf("No platforms support the %s extension.\n", icd_ext);
   
   /* Deallocate resources */
   free(platforms);
   return 0;
}
```

`Makefile`

```Makefile
PROJ=platform_ext_test

CC=gcc

CFLAGS=-std=c99 -Wall -DUNIX -g -DDEBUG

# Check for 32-bit vs 64-bit
PROC_TYPE = $(strip $(shell uname -m | grep 64))

# Check for Mac OS
OS = $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
DARWIN = $(strip $(findstring DARWIN, $(OS)))

# MacOS System
ifneq ($(DARWIN),)
	CFLAGS += -DMAC
	LIBS=-framework OpenCL

	ifeq ($(PROC_TYPE),)
		CFLAGS+=-arch i386
	else
		CFLAGS+=-arch x86_64
	endif
else

# Linux OS
LIBS=-lOpenCL
ifeq ($(PROC_TYPE),)
	CFLAGS+=-m32
else
	CFLAGS+=-m64
endif

# Check for Linux-AMD
ifdef AMDAPPSDKROOT
   INC_DIRS=. $(AMDAPPSDKROOT)/include
	ifeq ($(PROC_TYPE),)
		LIB_DIRS=$(AMDAPPSDKROOT)/lib/x86
	else
		LIB_DIRS=$(AMDAPPSDKROOT)/lib/x86_64
	endif
else

# Check for Linux-Nvidia
ifdef NVSDKCOMPUTE_ROOT
   INC_DIRS=. $(NVSDKCOMPUTE_ROOT)/OpenCL/common/inc
endif

endif
endif

$(PROJ): $(PROJ).c
	$(CC) $(CFLAGS) -o $@ $^ $(INC_DIRS:%=-I%) $(LIB_DIRS:%=-L%) $(LIBS)

.PHONY: clean

clean:
	rm $(PROJ)
```
</details>

## Accessing installed devices

- Khi truy cập được vào `vendor's platform`, ta có thể truy cập vào từng thiết bị đã kết nối được cung cấp bởi vendor. Trong một ứng dụng OpenCL, các `devices` nhận các `tasks` và `data` từ `host`.

- Các `devices` được biểu diễn bằng structure `cl_device_id`.

### Creating device structures

- Trước khi có thể gửi các `kernels` đến một `devices`, cần phải khởi tạo `cl_device_id` bằng hàm `clGetDeviceIDs`.

```cpp
cl_int clGetDeviceIDs(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id *devices, cl_uint *num_devices)
```
where:
> `platform`: <br>
> `device_type`: loại thiết bị kết nối.<br>
> `num_entries`: số thiết bị muốn kết nối.<br>
> `devices`: con trỏ chứa list thiết bị kết nối.<br>
> `num_devices`: số `devices` có kết nối.

|OpenCL device type|Meaning|
|:---:|---|
|`CL_DEVICE_TYPE_ALL`|Identifies all devices associated with the platform|
|`CL_DEVICE_TYPE_DEFAULT`|Identifies devices associated with the platform’s default type|
|`CL_DEVICE_TYPE_CPU`|Identifies the host processor|
|`CL_DEVICE_TYPE_GPU`|Identifies a device containing a graphics processor unit (GPU)|
|`CL_DEVICE_TYPE_ACCELERATOR`|Identifies an external device used to accelerate computation|

<details>
  <summary>EXAMPLE CODE!</summary>

```Cpp
cl_platform_id devs;
clGetDeviceIDs(plat, CL_DEVICE_TYPE_GPU, 3, devs, NULL);

cl_uint num_devices;
clGetDeviceIDs(plat, CL_DEVICE_TYPE_ACCELERATOR, 1, NULL, &num_devices);
```

</details>

### Obtaining device information

- Xác định loại thông tin thiết bị đang tìm kiếm.

```cpp
cl_int clGetDeviceInfo(cl_device_id device, cl_device_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
```
Bản chất giống với hàm [`clGetDeviceInfo`](#obtaining_platform_information).

|`param_name`|Output type|Purpose|
|:---:|:---:|---|
|`CL_DEVICE_NAME`|`char[]`|Returns the name of the device|
|`CL_DEVICE_VENDOR`|`char[]`|Returns the device’s vendor|
|`CL_DEVICE_EXTENSIONS`|`char[]`|Returns the device’s supported OpenCL extensions|
|`CL_DEVICE_GLOBAL_MEM_SIZE`|`cl_ulong`|Returns the size of the device’s global memory|
|`CL_DEVICE_ADDRESS_BITS`|`cl_uint`|Returns the size of the device’s address space|
|`CL_DEVICE_AVAILABLE`|`cl_bool`|Returns whether the device is available|
|`CL_DEVICE_COMPILER_AVAILABLE`|`cl_bool`|Returns whether the implementation provides a compiler for the device|

<details>
  <summary>The following code shows how this is accomplished!</summary>

```Cpp
char pform_vendor[40];
clGetPlatformInfo(platforms[0], CL_PLATFORM_VENDOR, sizeof(pform_vendor), &pform_vendor, NULL);
```

</details>

<details>
  <summary>EXAMPLE CODE!</summary>

`platform_ext_test.c`

```C++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MAC
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

int main() {

   /* Host/device data structures */
   cl_platform_id platform;
   cl_device_id dev;
   cl_uint addr_data;
   cl_int err;

   /* Extension data */
   char name_data[48], ext_data[4096];

   /* Identify a platform */
   err = clGetPlatformIDs(1, &platform, NULL);			
   if(err < 0) {			
      perror("Couldn't find any platforms");
      exit(1);
   }

   /* Access a device, preferably a GPU */
   /* Changed on 2/12 to fix the CL_INVALID_VALUE error */
   err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
   if(err == CL_DEVICE_NOT_FOUND) {
      err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
   }
   if(err < 0) {
      perror("Couldn't access any devices");
      exit(1);   
   }

   /* Access device name */
   err = clGetDeviceInfo(dev, CL_DEVICE_NAME, 		
      48 * sizeof(char), name_data, NULL);			
   if(err < 0) {		
      perror("Couldn't read extension data");
      exit(1);
   }

   /* Access device address size */
   clGetDeviceInfo(dev, CL_DEVICE_ADDRESS_BITS, 	
      sizeof(addr_data), &addr_data, NULL);			

   /* Access device extensions */
   clGetDeviceInfo(dev, CL_DEVICE_EXTENSIONS, 		
      4096 * sizeof(char), ext_data, NULL);			

   printf("NAME: %s\nADDRESS_WIDTH: %u\nEXTENSIONS: %s\n", 
      name_data, addr_data, ext_data);

   return 0;
}
```

`Makefile`

```Makefile
PROJ=device_ext_test

CC=gcc

CFLAGS=-std=c99 -Wall -DUNIX -g -DDEBUG

# Check for 32-bit vs 64-bit
PROC_TYPE = $(strip $(shell uname -m | grep 64))
 
# Check for Mac OS
OS = $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
DARWIN = $(strip $(findstring DARWIN, $(OS)))

# MacOS System
ifneq ($(DARWIN),)
	CFLAGS += -DMAC
	LIBS=-framework OpenCL

	ifeq ($(PROC_TYPE),)
		CFLAGS+=-arch i386
	else
		CFLAGS+=-arch x86_64
	endif
else

# Linux OS
LIBS=-lOpenCL
ifeq ($(PROC_TYPE),)
	CFLAGS+=-m32
else
	CFLAGS+=-m64
endif

# Check for Linux-AMD
ifdef AMDAPPSDKROOT
   INC_DIRS=. $(AMDAPPSDKROOT)/include
	ifeq ($(PROC_TYPE),)
		LIB_DIRS=$(AMDAPPSDKROOT)/lib/x86
	else
		LIB_DIRS=$(AMDAPPSDKROOT)/lib/x86_64
	endif
else

# Check for Linux-Nvidia
ifdef NVSDKCOMPUTE_ROOT
   INC_DIRS=. $(NVSDKCOMPUTE_ROOT)/OpenCL/common/inc
endif

endif
endif

$(PROJ): $(PROJ).c
	$(CC) $(CFLAGS) -o $@ $^ $(INC_DIRS:%=-I%) $(LIB_DIRS:%=-L%) $(LIBS)

.PHONY: clean

clean:
	rm $(PROJ)
```
</details>


## Managing devices with contexts
