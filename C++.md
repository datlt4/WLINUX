[<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/2d/Reference-com_logo.svg/1280px-Reference-com_logo.svg.png" height="15">](https://vnoi.info/library/56/4958/)
[<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/2d/Reference-com_logo.svg/1280px-Reference-com_logo.svg.png" height="15">](https://github.com/LuongTanDat/WLINUX/blob/master/learn_Makefiles_CMake.md)

# STANDARD TEMPLATE LIBRARY IN C++

Thư viện mẫu chuẩn STL trong C++ chia làm 4 thành phần là:

* Containers Library : chứa các cấu trúc dữ liệu mẫu (template) <a name="list_containers_library"></a>
    - Sequence containers
        - Vector
        - Deque
        - List
    - Containers adpators
        - Stack
        - Queue
        - Priority_queue
    - Associative containers
        - Set
        - Multiset
        - Map
        - Multimap
        - Bitset
* Algorithms Library: một số thuật toán để thao tác trên dữ liệu
* Iterator Library: giống như con trỏ, dùng để truy cập đến các phần tử dữ liệu của [container](#list_containers_library).
* Numeric library:

## ITERATOR (BIẾN LẶP)

Trong C++, một biến lặp là một đối tượng bất kì, trỏ tới một số phần tử trong 1 phạm vi của các phần tử (như mảng hoặc container), có khả năng để lặp các phần tử trong phạm vi bằng cách sử dụng một tập các toán tử (operators) (như so sánh, tăng `++` , ...)

Iterator có các toán tử như:

* So sánh: `==`,                                   `!=` giữa 2 iterator.
* Gán: `=` giữa 2 iterator.
* Cộng trừ: `+`,                                   `-` với hằng số và `++`,                                   `--`.
* Lấy giá trị: `*`.

## CONTAINERS (THƯ VIỆN LƯU TRỮ)

Một container là một đối tượng cụ thể lưu trữ một tập các đối tượng khác (các phần tử của nó).

Container xây dựng các cấu trúc thường sử dụng trong lập trình như: mảng động - dynamic arrays ( `vector` ), hàng đợi – queues ( `queue` ), hàng đợi ưu tiên – heaps ( `priority queue` ), danh sách kiên kết – linked list ( `list` ), cây – trees ( `set` ), mảng ánh xạ - associative arrays ( `map` )...

Tất cả các container ở 2 loại: Sequence container và Associative container.

### 1. Iterator:

<details>
  <summary>Click to expand code!</summary>

``` Cpp
#include <vector>

int main()
{
    /*khai báo iterator “it*/
    std::vector<int>::iterator it;
    std::vector<int> v1;

    /* trỏ đến vị trí phần tử đầu tiên của vector */
    it = v1.begin();

    /*trỏ đến vị trí kết thúc (không phải phần tử cuối cùng nhé) của vector) */
    it = v1.end();

    /* khai báo iterator ngược “rit */
    std::vector<int>::reverse_iterator rit;
    rit = v1.rbegin();

    /* trỏ đến vị trí kết thúc của vector theo chiều ngược (không phải phần tử đầu tiên nhé*/
    rit = v1.rend();
    return 0;
}
```

</details>

* Tất cả các hàm iterator này đều có độ phức tạp `O(1)`.

### 2. Vector (Mảng động):

* Sử dụng vector sẽ tốt khi:
    - Truy cập đến phần tử riêng lẻ thông qua vị trí của nó `O(1)`.
    - Chèn hay xóa ở vị trí cuối cùng `O(1)`.
* Vector làm việc giống như một __“mảng động__.

<details>
  <summary>Click to expand code!</summary>

``` cpp
#include <vector>

int main()
{
    /* Vector 1 chiều */
    /* tạo vector rỗng kiểu dữ liệu int */
    std::vector<int> first;

    /* tạo vector với 4 phần tử là 100 */
    std::vector<int> second(4, 100);

    /* lấy từ đầu đến cuối vector second */
    std::vector<int> third(second.begin(), second.end());

    /* copy từ vector third */
    std::vector<int> four(third);

    /* Vector 2 chiều */
    /* Tạo vector 2 chiều rỗng */
    std::vector<std::vector<int>> v1;

    /* khai báo vector 3x4 */
    std::vector<std::vector<int>> v2{
        {1, 2, 3, 0},
        {4, 5, 6, 0},
        {7, 8, 9, 0}};

    /* khai báo 5 vector 1 chiều rỗng  */
    std::vector<std::vector<int>> v3(5);

    /* khai báo vector 5*10 với các phần tử khởi tạo giá trị là 1 */
    std::vector<std::vector<int>> v4(5, std::vector<int>(10, 1));

    return 0;
}
```

</details>

#### Các phương thức:

* Capacity

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `size()` |Trả về số lượng phần tử của vector| `O(1)` |
| `empty()` |Trả về `true` (1) nếu vector rỗng, ngược lại là `false` (0)| `O(1)` |

* Truy cập tới phần tử

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
|operator `[]` |Trả về giá trị phần tử thứ `[#]` | `O(1)` |
| `at()` |Tương tự như trên| `O(1` )|
| `front()` |Trả về giá trị phần tử đầu tiên| `O(1)` |
| `back()` |Trả về giá trị phần tử cuối cùng| `O(1)` |

* Chỉnh sửa

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `push_back()` |Thêm vào ở cuối vector| `O(1)` |
| `pop_back()` |Loại bỏ phần tử ở cuối vector| `O(1)` |
| `insert(iterator,x)` |Chèn `x` vào trước vị trí `iterator` ( `x` có thể là phần tử hay `iterator` của 1 đoạn phần tử...)| `O(n)` |
| `erase()` |Xóa phần tử ở vị trí iterator| `O(n)` |
| `swap()` |Đổi 2 vector cho nhau (ví dụ: `first.swap(second)` ; )| `O(1)` |
| `clear()` |Xóa vector| `O(n)` |

<details>
  <summary>Click to expand code!</summary>

``` c
#include <iostream>
#include <vector>

std::vector<int> v;                     // Khai báo vector
std::vector<int>::iterator it;          // Khai báo iterator
std::vector<int>::reverse_iterator rit; // Khai báo iterator ngược
int i;

int main()
{
    for (i = 1; i <= 5; i++)
        v.push_back(i);                  // v={1,2,3,4,5}
    std::cout << v.front() << std::endl; // In ra 1
    std::cout << v.back() << std::endl;  // In ra 5
    std::cout << v.size() << std::endl;  // In ra 5
    v.push_back(9);                      // v={1,2,3,4,5,9}
    std::cout << v.size() << std::endl;  // In ra 6
    v.clear();                           // v={}
    std::cout << v.empty() << std::endl; // In ra 1 (vector rỗng)

    for (i = 1; i <= 5; i++)
        v.push_back(i);                 // v={1,2,3,4,5}
    v.pop_back();                       // v={1,2,3,4}
    std::cout << v.size() << std::endl; // In ra 4
    v.erase(v.begin() + 1);             // Xóa ptử thứ 1 v={1,3,4}
    v.erase(v.begin(), v.begin() + 2);  // v={4}
    v.insert(v.begin(), 100);           // v={100,4}
    v.insert(v.end(), 5);               // v={100,4,5}

    /*Duyệt theo chỉ số phần tử*/
    for (i = 0; i < v.size(); i++)
        std::cout << v[i] << " "; // 100 4 5
    std::cout << std::endl;

    /* Chú ý: Không nên viết        
    for (i = 0; i <= v.size() - 1; i++) ...      
    Vì nếu vector v rỗng thì sẽ dẫn đến sai khi duyệt !!!       
    */

    /*Duyệt theo iterator*/
    for (it = v.begin(); it != v.end(); it++)
        std::cout << *it << " ";
    // In ra giá trị ma iterator đang trỏ tới "100 4 5"
    std::cout << std::endl;

    /*Duyệt iterator ngược*/
    for (rit = v.rbegin(); rit != v.rend(); rit++)
        std::cout << *rit << " "; // 5 4 100
    std::cout << std::endl;

    return 0;
}
```

</details>

<details>
  <summary>Click to expand code!</summary>

``` c
#include <iostream>
#include <vector>

std::vector<std::vector<int>> a(10001);

//Khai báo vector 2 chiều với 10001 vector 1 chiều rỗng
int m, n, i, j, u, v;
int main()
{
    /* Input data */
    std::cin >> n >> m;
    for (i = 1; i <= m; i++)
    {
        std::cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    /* Sort cạnh kề */
    for (i = 1; i <= m; i++)
        sort(a[i].begin(), a[i].end());

    /* Print Result */
    for (i = 1; i <= m; i++)
    {
        for (j = 0; j < a[i].size(); j++)
            std::cout << a[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
}
```

</details>

### 3. Deque (Hàng đợi hai đầu):

* Deque (thuờng được phát âm giống như “deck) là từ viết tắt của __double-ended queue__ (hàng đợi hai đầu).

* Deque có các ưu điểm như:

    - Các phần tử có thể truy cập thông cua chỉ số vị trí của nó. `O(1)`
    - Chèn hoặc xóa phần tử ở cuối hoặc đầu của dãy. `O(1)`

``` Cpp
#include <deque>
```

#### Các phương thức:

* Capacity

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `size()` |Trả về số lượng phần tử của deque| `O(1)` |
| `empty()` |Trả về `true` (1) nếu deque rỗng, ngược lại là `false` (0)| `O(1)` |

* Truy cập tới phần tử

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
|operator `[]` |Trả về giá trị phần tử thứ `[#]` | `O(1)` |
| `at()` |Tương tự như trên| `O(1` )|
| `front()` |Trả về giá trị phần tử đầu tiên| `O(1)` |
| `back()` |Trả về giá trị phần tử cuối cùng| `O(1)` |

* Chỉnh sửa

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `push_back()` |Thêm vào ở cuối deque| `O(1)` |
| `pop_back()` |Loại bỏ phần tử ở cuối deque| `O(1)` |
| `insert(iterator,x)` |Chèn `x` vào trước vị trí `iterator` ( `x` có thể là phần tử hay `iterator` của 1 đoạn phần tử...)| `O(n)` |
| `erase()` |Xóa phần tử ở vị trí iterator| `O(n)` |
| `swap()` |Đổi 2 deque cho nhau (ví dụ: `first.swap(second)` ; )| `O(1)` |
| `clear()` |Xóa deque| `O(n)` |

### 4. List (Danh sách liên kết):

* List được thực hiện như danh sách nối kép (doubly-linked list). Mỗi phần tử trong danh sách nối kép có liên kết đến một phần tử trước đó và một phần tử sau nó. 
* Do đó, list có các ưu điểm như sau: 
    - Chèn và loại bỏ phần tử ở bất cứ vị trí nào trong container. `ĐPT O(1)`.
* Điểm yếu của list là khả năng truy cập tới phần tử thông qua vị trí. `ĐPT O(n)`.

``` Cpp
#include <list>
  ```

#### Các phương thức:

* Capacity

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `size()` |Trả về số lượng phần tử của list| `O(1)` |
| `empty()` |Trả về `true` (1) nếu deque rỗng, ngược lại là `false` (0)| `O(1)` |

* Truy cập tới phần tử

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `front()` |Trả về giá trị phần tử đầu tiên| `O(1)` |
| `back()` |Trả về giá trị phần tử cuối cùng| `O(1)` |

* Chỉnh sửa

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `push_back` | thêm phần tử vào ở cuối list| `ĐPT O(1)` |
| `push_front` | thêm phần tử vào đầu list| `ĐPT O(1)` |
| `pop_back` | loại bỏ phần tử ở cuối list| `ĐPT O(1)` |
| `pop_front` | loại bỏ phần tử ở đầu list| `ĐPT O(1)` |
| `insert (iterator, x)` | chèn `x` vào trước vị trí `iterator` ( x có thể là phần tử hay iterator của 1 đoạn phần tử...)| `ĐPT` là số phần tử thêm vào|
| `erase` | xóa phần tử ở vị trí iterator| `ĐPT` là số phần tử bị xóa đi|
| `swap` | đổi 2 list cho nhau (ví dụ| first.swap(second); )| `ĐPT O(1)` |
| `clear` | xóa list| `ĐPT O(n)` |

* Operations

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `splice` | di chuyển phần tử từ list này sang list khác| `ĐPT O(n)` |
| `remove (const)` | loại bỏ tất cả phần tử trong list bằng const| `ĐPT O(n)` |
| `remove_if (function)` | loại bỏ tất các phần tử trong list nếu hàm function return true | `ĐPT O(n)` |
| `unique` | loại bỏ các phần tử bị trùng lặp hoặc thỏa mãn hàm nào đó. Lưu ý: Các phần tử trong list phải được sắp xếp| `ĐPT O(n)` |
| `sort` | sắp xếp các phần tử của list| `ĐPT O(NlogN)` |
| `reverse` | đảo ngược lại các phần tử của list| `ĐPT O(n)` |

### 5. Stack (Ngăn xếp):

* Stack là một loại container adaptor, được thiết kế để hoạt động theo kiểu `LIFO` (Last - in first - out) (vào sau ra trước), tức là một kiểu danh sách mà việc bổ sung và loại bỏ một phần tử được thực hiển ở cuối danh sách. Vị trí cuối cùng của stack gọi là đỉnh (top) của ngăn xếp.

``` Cpp
#include <stack>
```

#### Các phương thức:

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `size` | trả về kích thước hiện tại của stack | `ĐPT O(1)` |
| `empty` | `true` stack nếu rỗng, và ngược lại | `ĐPT O(1)` |
| `push` | đẩy phần tử vào stack | `ĐPT O(1)` |
| `pop` | loại bỏ phẩn tử ở đỉnh của stack | `ĐPT O(1)` |
| `top` | truy cập tới phần tử ở đỉnh stack | `ĐPT O(1)` |

<details>
  <summary>Click to expand code!</summary>

``` Cpp
#include <iostream>
#include <stack>

std::stack<int> s;
int i;

int main()
{
    for (i = 1; i <= 5; i++)
        s.push(i);                       // s={1,2,3,4,5}
    s.push(100);                         // s={1,2,3,4,5,100}
    std::cout << s.top() << std::endl;   // In ra 100
    s.pop();                             // s={1,2,3,4,5}
    std::cout << s.empty() << std::endl; // In ra 0
    std::cout << s.size() << std::endl;  // In ra 5
    return 0;
}
```

</details>

### 6. Queue (Hàng đợi):

* Queue là một loại container adaptor, được thiết kế để hoạt động theo kiểu FIFO (First - in first - out) (vào trước ra trước), tức là một kiểu danh sách mà việc bổ sung được thực hiển ở cuối danh sách và loại bỏ ở đầu danh sách. 
* Trong queue, có hai vị trí quan trọng là vị trí đầu danh sách (front), nơi phần tử được lấy ra, và vị trí cuối danh sách (back), nơi phần tử cuối cùng được thêm vào.

``` Cpp
#include <queue>
```

#### Các phương thức:

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `size` | trả về kích thước hiện tại của queue| `ĐPT O(1)` |
| `empty` | `true` nếu queue rỗng, và ngược lại| `ĐPT O(1)` |
| `push` | đẩy vào cuối queue| `ĐPT O(1)` |
| `pop` |loại bỏ phần tử (ở đầu)| `ĐPT O(1)` |
| `front` | trả về phần tử ở đầu| `ĐPT O(1)` |
| `back` |trả về phần tử ở cuối| `ĐPT O(1)` |

<details>
  <summary>Click to expand code!</summary>

``` cpp
#include <iostream>
#include <queue>

std::queue<int> q;
int i;

int main()
{
    for (i = 1; i <= 5; i++)
        q.push(i);                       // q={1,2,3,4,5}
    q.push(100);                         // q={1,2,3,4,5,100}
    std::cout << q.front() << std::endl; // In ra 1
    q.pop();                             // q={2,3,4,5,100}
    std::cout << q.back() << std::endl;  // In ra 100
    std::cout << q.empty() << std::endl; // In ra 0
    std::cout << q.size() << std::endl;  // In ra 5
    return 0;
}
```

</details>

### 7. Priority Queue (Hàng đợi ưu tiên):

* Priority queue là một loại container adaptor, được thiết kế đặc biệt để phần tử ở đầu luôn luôn lớn nhất (theo một quy ước về độ ưu tiên nào đó) so với các phần tử khác. 
* Nó giống như một heap, mà ở đây là heap max, tức là phần tử có độ ưu tiên lớn nhất có thể được lấy ra và các phần tử khác được chèn vào bất kì. 
* Phép toán so sánh mặc định khi sử dụng priority queue là phép toán less (Xem thêm ở thư viện functional) 
* Để sử dụng priority queue một cách hiệu quả, các bạn nên học cách viết hàm so sánh để sử dụng cho linh hoạt cho từng bài toán.

``` Cpp
#include <queue>
```

### 8. Set (Tập hợp):

* Set là một loại associative containers để lưu trữ các phần tử không bị trùng lặp (unique elements), và các phần tử này chính là các khóa (keys).
* Khi duyệt set theo iterator từ begin đến end, các phần tử của set sẽ tăng dần theo phép toán so sánh. 
* Mặc định của set là sử dụng phép toán less, bạn cũng có thể viết lại hàm so sánh theo ý mình. 
* Set được thực hiện giống như cây tìm kiếm nhị phân (Binary search tree).

#### Khai báo:

``` Cpp
#include <set> 
std::set<int, std::less<int>> s;
std::set<int, std::greater<int>> s;
```

Hoặc viết class so sánh theo ý mình:

``` Cpp
struct cmp
{
    bool operator()(int a, int b) { return a < b; }
};
std::set<int, cmp> myset;
```

#### Các phương thức:

* Capacity

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `size` | trả về kích thước hiện tại của set | `ĐPT O(1)` |
| `empty` | `true` nếu set rỗng, và ngược lại | `ĐPT O(1)` |

* Modifiers

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `insert` | Chèn phần tử vào set | `ĐPT O(logN)` |
| `erase` | có 2 kiểu xóa: xóa theo iterator, hoặc là xóa theo khóa | `ĐPT O(logN)` |
| `clear` | xóa tất cả set | `ĐPT O(n)` |
| `swap` | đổi 2 set cho nhau | `ĐPT O(n)` |

* Operations

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `find` | trả về itarator trỏ đến phần tử cần tìm kiếm. Nếu không tìm thấy itarator trỏ về “end của set | `ĐPT O(logN)` |
| `lower_bound` | trả về iterator đến vị trí phần tử bé nhất mà không bé hơn (lớn hơn hoặc bằng) khóa (dĩ nhiên là theo phép so sánh), nếu không tìm thấy trả về vị trí “end của set | `ĐPT O(logN)` |
| `upper_bound` | trả về iterator đến vị trí phần tử bé nhất mà lớn hơn khóa, nếu không tìm thấy trả về vị trí “end của set | `ĐPT O(logN)` | 
| `count` | trả về số lần xuất hiện của khóa trong container. Nhưng trong set, các phần tử chỉ xuất hiện một lần, nên hàm này có ý nghĩa là sẽ return 1 nếu khóa có trong container, và 0 nếu không có | `ĐPT O(logN)` |

<details>
  <summary>Click to expand code!</summary>

``` cpp
#include <iostream>
#include <set>

int main()
{
    std::set<int> s;
    std::set<int>::iterator it;
    s.insert(9);                          // s={9}
    s.insert(5);                          // s={5,9}
    std::cout << *s.begin() << std::endl; //In ra 5
    s.insert(1);                          // s={1,5,9}
    std::cout << *s.begin() << std::endl; // In ra 1

    it = s.find(5);
    if (it == s.end())
        std::cout << "Khong co trong container" << std::endl;
    else
        std::cout << "Co trong container" << std::endl;

    s.erase(it); // s={1,9}
    s.erase(1);  // s={9}

    s.insert(3); // s={3,9}
    s.insert(4); // s={3,4,9}

    it = s.lower_bound(4);
    if (it == s.end())
        std::cout << "Khong co phan tu nao trong std::set khong be hon 4" << std::endl;
    else
        std::cout << "Phan tu be nhat khong be hon 4 la " << *it << std::endl; // In ra 4

    it = s.lower_bound(10);
    if (it == s.end())
        std::cout << "Khong co phan tu nao trong std::set khong be hon 10" << std::endl;
    else
        std::cout << "Phan tu be nhat khong be hon 10 la " << *it << std::endl; // Khong co ptu nao

    it = s.upper_bound(4);
    if (it == s.end())
        std::cout << "Khong co phan tu nao trong std::set lon hon 4" << std::endl;
    else
        std::cout << "Phan tu be nhat lon hon 4 la " << *it << std::endl; // In ra 9

    /* Duyet std::set */

    for (it = s.begin(); it != s.end(); it++)
    {
        std::cout << *it << " ";
    }
    // In ra 3 4 9

    std::cout << std::endl;
    return 0;
}

```

</details>

### 9. Mutiset (Tập hợp):

* Multiset giống như Set nhưng có thể chứa các khóa có giá trị giống nhau. 
* Khai báo : giống như set.

### 10. Map (Ánh xạ):

* Map là một loại associative container. Mỗi phần tử của map là sự kết hợp của khóa (key value) và ánh xạ của nó (mapped value). Cũng giống như set, trong map không chứa các khóa mang giá trị giống nhau. 
* Trong map, các khóa được sử dụng để xác định giá trị các phần tử. Kiểu của khóa và ánh xạ có thể khác nhau. 
* Và cũng giống như set, các phần tử trong map được sắp xếp theo một trình tự nào đó theo cách so sánh. 
* Map được cài đặt bằng red-black tree (cây đỏ đen) – một loại cây tìm kiếm nhị phân tự cân bằng. Mỗi phần tử của map lại được cài đặt theo kiểu pair (xem thêm ở thư viện utility).

#### Khai báo:

``` Cpp
#include <map>
std::map <kiểu_dữ_liệu_1, kiểu_dữ_liệu_2>
// kiểu dữ liệu 1 là khóa, kiểu dữ liệu 2 là giá trị của khóa.
```

Hoặc viết class so sánh theo ý mình:

``` Cpp
#include <map>
struct cmp{
  bool operator() (char a, char b) {return a<b;}
};
std::map <char, int, cmp> m;
```

#### Các phương thức:

* Capacity

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `size` | trả về kích thước hiện tại của map | `ĐPT O(1)` |
| `empty` | `true` nếu map rỗng, và ngược lại | `ĐPT O(1)` |

* Truy cập tới phần tử: 

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `operator [khóa]` | Nếu khóa đã có trong map, thì hàm này sẽ trả về giá trị mà khóa ánh xạ đến. Ngược lại, nếu khóa chưa có trong map, thì khi gọi [] nó sẽ thêm vào map khóa đó | `ĐPT O(logN)` |

* Chỉnh sửa 

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `insert` | Chèn phần tử vào map. Chú ý: phần tử chèn vào phải ở kiểu `pair` | `ĐPT O(logN)` |
| `erase` |  xóa theo iterator, xóa theo khóa trong map | `ĐPT O(logN)` |
| `clear` | xóa tất cả set | `ĐPT O(n)` |
| `swap` | đổi 2 set cho nhau | `ĐPT O(n)` |

* Operations: 

|Phương thức|Mô tả|Độ phức tạp|
|:---:|---|:---:|
| `find` | trả về itarator trỏ đến phần tử cần tìm kiếm. Nếu không tìm thấy iterator trỏ về “end của map | `ĐPT O(logN)` |
| `lower_bound` | trả về iterator đến vị trí phần tử bé nhất mà không bé hơn (lớn hơn hoặc bằng) khóa (dĩ nhiên là theo phép so sánh), nếu không tìm thấy trả về vị trí “end của map | `ĐPT O(logN)` |
| `upper_bound` |trả về iterator đến vị trí phần tử bé nhất mà lớn hơn khóa, nếu không tìm thấy trả về vị trí “end của map | `ĐPT O(logN)` |
| `count` | trả về số lần xuất hiện của khóa trong multiset | `ĐPT O(logN)` |

<details>
  <summary>Click to expand code!</summary>

``` cpp
#include <iostream>
#include <map>

int main()
{
    std::map<char, int> m;
    std::map<char, int>::iterator it;

    m['a'] = 1;                             // m={{'a',1}}
    m.insert(std::make_pair('b', 2));       // m={{'a',1};{'b',2}}
    m.insert(std::pair<char, int>('c', 3)); // m={{'a',1};{'b',2};{'c',3}}

    std::cout << m['b'] << std::endl; // In ra 2
    m['b']++;                         // m={{'a',1};{'b',3};{'c',3}}

    it = m.find('c'); // it point to key 'c'

    std::cout << it->first << std::endl;  // In ra 'c'
    std::cout << it->second << std::endl; // In ra 3

    m['e'] = 100; // m={{'a',1};{'b',3};{'c',3};{'e',100}}

    it = m.lower_bound('d');              // it point to 'e'
    std::cout << it->first << std::endl;  // In ra 'e'
    std::cout << it->second << std::endl; // In ra 100

    return 0;
}

```

</details>

## STL ALGORITHMS (THƯ VIỆN THUẬT TOÁN)

### 1. Min, Max:

* `min`: trả về giá trị bé hơn theo phép so sánh (mặc định là phép toán `less`)

Ví dụ: `min('a','b')` sẽ return `'a'` ; `min(3,1)` sẽ return `1` ; 

* `max`: thì ngược lại với hàm min

Ví dụ: `max('a,'b')` sẽ return `'b'` , `max(3,1)` sẽ return `1` .

* `next_permutation`: hoán vị tiếp theo. Hàm này sẽ return `1` nếu có hoán vị tiếp theo,            `0` nếu không có hoán vị tiếp theo.

* `prev_permution`: ngược lại với `next_permutation`

<details>
  <summary>Ví dụ:</summary>

``` cpp
// next_permutation
#include <iostream>
#include <algorithm>

int main()
{
    int myints[] = {1, 2, 3};
    std::cout << "The 3! possible permutations with 3 elements:\n";
    do
    {
        std::cout << myints[0] << " " << myints[1] << " " << myints[2] << std::endl;
    } while (std::next_permutation(myints, myints + 3));
    return 0;
}
```

__Output:__

``` bash
The 3! possible permutations with 3 elements:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
4 2 1
```

</details>

### 2. Sắp xếp:

* `sort`: sắp xếp đoạn phần tử theo một trình tự nào đó. Mặc định của `sort` là sử dụng operator `<`.
* Bạn có thể sử dụng hàm so sánh, hay class so sánh tự định nghĩa để sắp xếp cho linh hoạt.

<details>
  <summary>Click to expand code!</summary>

``` cpp
// sort algorithm example
#include <iostream>
#include <algorithm>

bool myfunction(int i, int j) { return (i < j); }
struct myclass
{
    bool operator()(int i, int j) { return (i > j); }
} myobject; 

int main()
{
    int myints[] = {32, 71, 12, 45, 26, 80, 53, 33};

    // using default comparison (operator <):
    std::sort(myints, myints + 4); //(12 32 45 71)26 80 53 33

    // using function as comp
    std::sort(myints + 4, myints + 8, myfunction); // 12 32 45 71(26 33 53 80)
    for (int i = 0; i < 8; i++)
        std::cout << myints[i] << " ";
    std::cout << std::endl;

    // using object as comp
    std::sort(myints, myints + 8, myobject); //(80 71 53 45 33 32 26 12)
    for (int i = 0; i < 8; i++)
        std::cout << myints[i] << " ";
    std::cout << std::endl;

    return 0;
}
```

</details>

### 3. Tìm kiếm nhị phân (các hàm đối với đoạn đã sắp xếp):

#### binary_search:

* tìm kiếm xem khóa có trong đoạn cần tìm không. Lưu ý: đoạn tìm kiếm phải được sắp xếp theo một trật tự nhất đinh. Nếu tìm được sẽ return true, ngược lại return false.
* Dạng 1: `binary_search(vị trí bắt đầu, vị trí kết thúc, khóa);`
* Dạng 2: `binary_search(vị trí bắt đầu, vị trí kết thúc, khóa, phép so sánh);`

<details>
  <summary>Click to expand code!</summary>

``` cpp
// binary_search example
#include <iostream>
#include <algorithm>
#include <vector>

bool myfunction(int i, int j) { return (i < j); }
int main()
{
    int myints[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    std::vector<int> v(myints, myints + 9); // 1 2 3 4 5 4 3 2 1

    // Sử dụng toán tử so sánh mặc định
    std::sort(v.begin(), v.end());
    std::cout << "looking for a 3... ";
    if (std::binary_search(v.begin(), v.end(), 3))
        std::cout << "found!\n";
    else
        std::cout << "not found.\n";

    // sử dụng hàm so sánh tự định nghĩa:
    std::sort(v.begin(), v.end(), myfunction);
    std::cout << "looking for a 6... ";
    if (std::binary_search(v.begin(), v.end(), 6, myfunction))
        std::cout << "found!\n";
    else
        std::cout << "not found.\n";

    return 0;
}
```

</details>

#### lower_bound, upper_bound:

* Hàm lower_bound và upper_bound tương tự như ở trong container set hay map.
* `lower_bound` trả về iterator đến phần tử đầu tiên trong nửa đoạn `[first,last]` mà không bé hơn khóa tìm kiếm.
    - `Dạng 1: lower_bound( đầu , cuối , khóa );`
    - `Dạng 2: lower_bound( đầu , cuối , khóa , phép toán so sánh của đoạn);`
* `upper_bound` trả về iterator đến phần tử đầu tiên trong nửa đoạn `[first, last]` mà lớn hơn khóa tìm kiếm.
    - `Dạng 1: upper_bound ( đầu , cuối , khóa );`
    - `Dạng 2: upper_bound ( đầu , cuối , khóa, phép toán so sánh của đoạn);`

<details>
  <summary>Click to expand code!</summary>

``` cpp
// lower_bound/upper_bound example
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    int myints[] = {10, 20, 30, 30, 20, 10, 10, 20};
    std::vector<int> v(myints, myints + 8); // 10 20 30 30 20 10 10 20
    std::vector<int>::iterator low, up;
    std::sort(v.begin(), v.end());             // 10 10 10 20 20 20 30 30
    low = lower_bound(v.begin(), v.end(), 20); //          ^
    up = upper_bound(v.begin(), v.end(), 20);  //                   ^
    std::cout << "lower_bound at position " << int(low - v.begin()) << std::endl;
    std::cout << "upper_bound at position " << int(up - v.begin()) << std::endl;
    return 0;
}
```

__Output:__

``` 

lower_bound at position 3
upper_bound at position 6
```

</details>

## THƯ VIỆN STRING C++

* `String` là một kiểu đặc biệt của container, thiết kế đặc để hoạt động với các chuỗi kí tự.
* Nhập, xuất `string`:
    - Sử dụng toán tử `>>` : Nhập đến khi gặp dấu cách.
    - Sử dụng `getline`: Nhập cả một dòng kí tự (chứa cả dấu cách nếu có) cho string.
    - Xuất string: sử dụng toán tử `<<` như bình thuờng.

#### Khai báo:

``` Cpp
#include <string> 
```

#### Các phương thức:

* Trong `string` bạn có thể sử dụng các toán tử `=` để gán giá trị cho string, hay toán tử `+` để nối hai string với nhau, hay toán tử `==`,   `!=` để so sánh.

* Capacity:

|Phương thức|Mô tả|
|:---:|---|
| `size` | trả về độ dài của string |
| `length` | trả về độ dài của string |
| `clear` |  xóa string |
| `empty` | return true nếu string rỗng, false nếu ngược lại |

* Truy cập đến phần tử:

|Phương thức|Mô tả|
|:---:|---|
| `operator [chỉ_số]` | lấy kí tự vị trí chỉ_số của string|

* Chỉnh sửa:

|Phương thức|Mô tả|
|:---:|---|
| `push_back`| chèn kí tự vào sau string|
| `insert (n, x)`|chèn x vào string ở trước vị trí thứ n. x có thể là string, char, ...|
| `erase (pos, n)`| xóa khỏi string `n` kí tự bắt đầu từ vị trí thứ `pos`.|
| `erase (iterator)`| xóa khỏi string phần tử ở vị trí iterator.|
| `replace (pos, size, s1)`| thay thế string từ vị trí `pos`, số phần tử thay thế là `size` và thay bằng xâu s1|
| `swap (string_cần_đổi)` | đổi giá trị 2 xâu cho nhau. |

- String operations:

|Phương thức|Mô tả|
|:---:|---|
| `c_str` | chuyển xâu từ dạng string trong C++ sang string trong C.|
| `substr (pos,length)` | return string được trích ra từ vị trí thứ `pos`, và trích ra `length` kí tự.|