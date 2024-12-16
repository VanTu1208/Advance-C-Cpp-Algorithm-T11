# Advance-C-Cpp-Algorithm-T11
## Bài 2: STDARG - ASSERT
<details><summary>Xem</summary>
 
### Thư viện STDARG
 > **Cung cấp các phương thức để làm việc với hàm có tham số đầu vào chưa xác định**

**Bao gồm:**
```cpp
va_list: Kiểu dữ liệu cho các đối tượng lưu danh sách có đối số biến đổi

va_start(v,l): Cần được gọi trước khi truy cập các đối số trong danh sách v, hoặc có chức năng tách phần tử đầu tiên l ra khỏi danh sách

va_arg(v,l): Truy cập lần lượt một đối số trong danh sách v và ép kiểu theo l

va_copy(d,s): copy danh sách s và gán vào danh sách d

va_end(v): Kết thúc việc sử dụng danh sách đối số biến đổi, được gọi trước khi kết thúc hàm.
```
**Ví dụ: Tính tổng danh sách đối số biến đổi**
<details><summary>Xem Code và giải thích</summary>
<p>

```cpp
#include <stdio.h>
#include <stdarg.h>

#define sumUnDefine(...)  sum(__VA_ARGS__,"\n")

int sum(int count1,...)
{
    va_list args1;
    va_list check;

    va_start(args1, count1);
    va_copy(check, args1);

    int result1 = count1;

    while ((va_arg(check, char*)) != (char*)"\n")
    {
        result1 += va_arg(args1, int);
    }
    va_end(args1);

    return result1;
}
```
**Giải thích**

```cpp
+) va_list args1; //Tạo ra một biến args1 chứa chuỗi kỹ tự gồm các đối số của hàm.

+) a_start(args1, count1); //Tách chuỗi count1 ra khỏi args1 và bắt đầu xử lý danh s+ách

+) va_copy(check, args1); //Copy danh sách args1 vào danh sách check1

+) int result1 = count1; //Giá trị đầu của kết quả là tham số thứ nhất

+) while ((va_arg(check, char*)) != (char*)"\n") //Kiểm tra việc kết thúc chuỗi, sử dụng check để tránh việc gọi hai lần dữ liệu của args1 gây ra thiếu kết quả.

+) result += va_arg(args1, int); //Đọc lần lượt từng phần tử của danh sách và ép kiểu về số nguyên sau đó cộng dồn vào kết quả

+) va_end(args); //Thu hồi lại địa chỉ biến args và kết thúc việc xử lý

+) printf("Tong khong xac dinh: %d\n", sumUnDefine(3, 4, 5, 6, 7)); //Gọi hàm thực thi in ra kết quả
```
**Kết quả:**

```cpp
Tong khong xac dinh: 25
```

</p>
</details>

### Thư viện ASSERT
 > **Cung cấp các macro sử dụng để kiểm tra điều kiện, nếu điều kiện sai(false), dừng chương trình và báo lỗi**

> **#define NDEBUG để tắt debug**

**Ví dụ: Tính tổng danh sách đối số biến đổi**
<details><summary>Xem Code và giải thích</summary>
<p>

```cpp
#include <stdio.h>
#include <assert.h>


//Nếu b = 0 thì lỗi và dừng chương trình

float divide(int a, int b){
    assert(b != 0 && "b bang 0");
    return (double)a/b;
}


int main(){
    printf("a = ");
    int a, b;
    scanf("%d", &a);
   
    printf("\nb = ");
    scanf("%d", &b);

    printf("\n%d/%d = %f\n",a,b,divide(a,b));
}
```
**Giải thích**

```cpp
+) assert(b != 0 && "b bang 0"); // Kiểm tra điều kiện nếu b khác 0 (false) thì dừng chương trình và in ra
"b bang 0"
```
**Kết quả:**
```cpp
a = 5  
b = 0  
Assertion failed: b != 0 && "b bang 0", file main.c, line 8
```
</p>
</details>

</details>

## Bài 3: POINTER
<details><summary>Xem</summary>
 
**Pointer** là một biến chứa địa chỉ của một đổi tượng khác (biến, mảng, hàm), giúp chúng ta xử lý các thao tác trên bộ nhớ linh hoạt hơn.

**Ví dụ:**  
Biến bình thường: ```int A = 5```;
- Có Address giả sử ```0xA1```;
- Giá trị 5
Thì biến con trỏ ```int *ptrA = &A```; 
- Có Address giả sử ```0x42```;
- Có giá trị là địa chỉ của biến A: ```0xA1```
Cách giải tham chiếu để lấy ra giá trị của A từ ptrA  
Ta có:
- ```ptrA = 0xA1```
- ```&ptrA = 0x42``` (lấy địa chỉ của con trỏ)
- ```*prtA = *(0xA1) = 5``` (giải tham chiếu)
Vì thế nếu 
```
int *ptr = &X; //ptr trỏ đến địa chỉ của x 
int y = *ptr; // y = giá trị tại địa chỉ ptr trỏ tới
```
Thì ```y = x```  

**Kích thước của con trỏ** phụ thuộc vào **kiến trúc máy tính** và **trình biên dịch**. Ví dụ STM32 thì con trỏ có kích thước 32bits

Ví dụ ```int *ptrA``` và ```char *ptrB``` đều có kích thước như nhau. **Khác nhau** là khi đọc dữ liệu từ địa chỉ của con trỏ sẽ đọc số byte bằng với kiểu dữ liệu của con trỏ đó. Như y = *ptrA, y sẽ là dữ liệu 4 byte sau địa chỉ của con trỏ

**Mảng** có các phần tử với địa chỉ liền kề với nhau, cách nhau số bit phụ thuộc vào kiểu dữ liệu của mảng. Mảng mặc định sẽ trỏ đến phần tử đầu tiên.

**Ví dụ:** cho mảng 
```int A[] = {3,1,2};
int *ptrA = A; // Lúc này ptrA trỏ tới A[0] ví dụ 0x02

```
Thì ```prtA+1``` sẽ trỏ tới ```0x06```  tức trỏ tới ```A[1]``` hoặc ```prtA+2``` sẽ trỏ tới ```A[2]```

Muốn lấy giá trị ```A[2]``` tức là ```*(ptrA+2)```

### Ví dụ đọc dữ liệu của biến và mảng:
```cpp
#include <stdio.h>

int a = 15;
int *ptrA = &a;

float b = 20;
float *ptrB = &b;

float arr[] = {2,3,4,5,6,7};
float *ptrArr = arr;

int main(){
    printf("Gia tri cua A la: %d\n",*ptrA);
    printf("Gia tri cua B la: %f\n",*ptrB);
    for(int i = 0; i < 6; i++){
        printf("Gia tri cua Arr[%d] la: %f\n",i,*(ptrArr+i)); //ptrArr: 0xA0, //prtArr1: 0xA4, //PtrArr2: 0xA8 (4 byte của float)
    }
    return 0;
}

```
Kết quả:
```cpp
Gia tri cua A la: 15
Gia tri cua B la: 20.000000    
Gia tri cua Arr[0] la: 2.000000
Gia tri cua Arr[1] la: 3.000000
Gia tri cua Arr[2] la: 4.000000
Gia tri cua Arr[3] la: 5.000000
Gia tri cua Arr[4] la: 6.000000
Gia tri cua Arr[5] la: 7.000000
```
Ta có ptrA và ptrB trỏ đến địa chỉ của A và B. Nên khi giải tham chiếu sẽ được giá trị của A và B là 15 và 20.

Với mảng arr ta có ptrArr trỏ tới arr[0]. Muốn đọc các phần tử tiếp theo thì sẽ cộng số thứ tự phần tử tưởng ứng và được kết quả như trên.


Ví dụ hoán đổi hai giá trị:
```cpp
#include <stdio.h>

void swapINCORRECT(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

void swapCORRECT(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 10;
    int b = 30;
    swapINCORRECT(a, b);
    printf("a = %d\n",a);
    printf("b = %d\n",b);
    
    swapCORRECT(&a, &b);
    printf("a = %d\n",a);
    printf("b = %d\n",b);

    return 0;
}
```
Kết quả:
```cpp
a = 10
b = 30
a = 30
b = 10
```

Ta có với hàm ```swapINCORRECT(int a, int b)``` tham số truyền vào là hai biến a và b, và trình biên dịch khi chạy hàm này sẽ tạo ra hai biến a, b với địa chỉ khác sau đó hoán đổi và thu hồi khi hoàn thành hàm, nên sau khi hàm này được thực thi thì hai biến a = 10 và b = 30 không thay đổi vị trí cho nhau, dẫn đến kết quả không chính xác

Với hàm ```swapCORRECT(int *a, int *b)``` tham số truyền vào là hai con trỏ và khi gọi hàm thực thi ```swapCORRECT(&a, &b)``` sẽ truyền vào địa chỉ của hai biến a và b nên giá trị của hai biến này có thể truy cập và thay đổi được
```cpp
    int temp = *a; // Temp = 10
    *a = *b; // giá trị của a = giá trị của b
    *b = temp; // giá trị của b = temp
```
### Các loại con trỏ
#### 1. Void Pointer
- Là biến có thể trỏ tới bất kỳ kiểu dữ liệu nào mà không cần biết kiểu dữ liệu của giá trị tại địa chỉ đó
- Cú pháp ```void *ptr;``` 
**Ví dụ:**
```cpp
#include <stdio.h>

void *ptr;

int main(){
    int A = 10;
    float B = 25.4;

    ptr = &A;

    printf("Dia chi cua A: %p\n",ptr);
    printf("Gia tri cua A: %d\n",*(int*)ptr);

    ptr = &B;
    printf("Dia chi cua B: %p\n",ptr);

    printf("Gia tri cua A: %f",*(float*)ptr);
}
```
Kết quả
```cpp
Dia chi cua A: 0000008EF87FFBAC
Gia tri cua A: 10
Dia chi cua B: 0000008EF87FFBA8
Gia tri cua A: 25.400000
```
Ta không thể đọc giá trị của A qua ptr trực tiếp vì trình biên dịch không biết ptr cần đọc bao nhiêu byte, vì thế ta phải ép kiểu con trỏ sang kiểu con trỏ số nguyên phù hợp với A```(int*)ptr```. Sau đó giải tham chiếu để được giá trị ```*(int*)ptr```. Tương tự với float B.

#### 2. Function Pointer
- Con trỏ hàm là một biến giữ địa chỉ của một hàm, nó trỏ đến vị trí bộ nhớ chứa mã máy của hàm
- Con trỏ hàm cho phép truyền một hàm như một đối số cho một hàm khác, lưu trữ địa chỉ của hàm trong một cấu trúc dữ liệu, hoặc thậm chí truyền hàm như một giá trị trả về tự một hàm khác.
- Để trỏ đến hàm, con trỏ hàm phải có cùng kiểu dữ liệu trả về và các tham số truyền vào cũng phải có cùng kiểu dữ liệu với hàm đó.
- Có hai cách để lấy địa chỉ hàm: Lấy trực tiếp tên hoặc thêm dấu ```&``` phía trước hàm
**Ví dụ:**
```cpp
#include <stdio.h>

int sum(int Arr[], int num){
    int result = 0;
    for(int i = 0; i < num; i++){
        result += Arr[i];
    }
    return result;
}

float sub(float a, int b){
    printf("Ket qua: %f - %d =  %f\n", a, b, a-b);
    return (a - b);
}

int main(){
    int Array[] = {3,1,2,5,6};
    
    int (*ptr)(int*, int) = sum ;
    printf("Tong mang la: %d\n", ptr(Array, 5));

    float (*ptr1)(float,int) = sub;
    ptr1(9.8, 6.9);

    return 0;

}
```
- Để tạo con trỏ hàm trỏ tới hàm sub: ```float (*ptr1)(float,int) = sub;```
- Tạo con trỏ hàm trỏ tới hàm sum: ```int (*ptr)(int*, int) = sum;```. Tham số đầu tiên truyền vào là con trỏ số nguyên vì với hàm, tham số là một mảng sẽ được biến đổi thành con trỏ khi biên dịch, thành con trỏ trỏ tới địa chỉ đầu tiên của mảng.
- Sau đó gọi hàm thực thi
    - ```ptr(Array, 5);```
    - ```ptr1(9.8, 6.9);```
Kết quả:
```
Tong mang la: 17
Ket qua: 9.800000 - 6 =  3.800000
```
Kết quả của phép trừ bị sai vì khi thực thi ta truyền vào hai số kiểu float nhưng khai báo kiểu (float, int) nên sẽ tự động ép kiểu thành int nên 6.9 sẽ thành 6 và thực hiện phép trừ. 

**Ví dụ: Mảng con trỏ hàm**
```cpp
#include <stdio.h>

int sum(int a,int b){
    printf("Ket qua: %d + %d =  %d\n", a, b, a+b);
    return (a+b);
}

int sub(int a, int b){
    printf("Ket qua: %d - %d =  %d\n", a, b, a-b);
    return (a - b);
}

int main(){
  
    int(*ptr[])(int, int) = {sum, sub};
    
    ptr[0](2, 5);
   
    ptr[1](9,7);
    
    return 0;
}
```
Kết quả: 
```
Ket qua: 2 + 5 =  7
Ket qua: 9 - 7 =  2
```
- ```int(*ptr[])(int, int) = {sum, sub};``` Khai báo mảng con trỏ trả về kiểu dữ liệu int, hai tham số truyền vào là int, gồm hai phần tử là địa chỉ của hai hàm sum và sub. Tức ```ptr[0]``` trỏ tới địa chỉ hàm ```sum``` và ```ptr[1]``` trỏ tới địa chỉ hàm ```sub```
- Gọi hàm thực thi 
```    
ptr[0](2, 5);
ptr[1](9,7);
```

**Ví dụ truyền con trỏ cho hàm khác**
```cpp
#include <stdio.h>

int sum(int a,int b){
    printf("Ket qua: %d + %d =  %d\n", a, b, a+b);
    return (a+b);
}

int sub(int a, int b){
    printf("Ket qua: %d - %d =  %d\n", a, b, a-b);
    return (a - b);
}

void caculate(int(*ptr)(int,int), int a,int b){
    ptr(a, b);
}


int main(){

    caculate(sum, 6, 7);
    caculate(sub, 8, 2);
    
    return 0;
}
```
Kết quả:    
```
Ket qua: 6 + 7 =  13
Ket qua: 8 - 2 =  6
```
- Hàm ```void caculate(int(*ptr)(int,int), int a,int b)``` sẽ truyền vào ba tham số gồm một con trỏ hàm và hai biến số nguyên để tính toán. Và sẽ địa chỉ hàm ứng với con trỏ được truyền vào ```ptr(a, b);```


#### 3. Pointer to Constant (Con trỏ hằng)
- Là con trỏ không thể thay đổi giá trị mà nó trỏ đến thông qua giải tham chiếu nhưng giá trị tại địa chỉ đó có thể thay đổi thông qua biến gốc
- Khai báo: ```int const *ptr;``` hoặc ```const int *ptr;``` 

**Ví dụ: Con trỏ hằng**
```cpp
#include <stdio.h>

int a = 5;
int b = 20;

int *ptrA = &a;
int const *ptrB = &b;

int main(){

    *ptrA = 10;
    printf("a = %d", *ptrA);

    *ptrB = 8;
    printf("b = %d", *ptrB);
    return 0;
}
```
- Ta có hai con trỏ ptrA và con trỏ hằng ptrB, ta chỉ có thể thay đổi giá trị của a bằng giải tham chiếu nhưng không thể thay đổi giá trị của b vì con trỏ hằng không được phép thay đổi giá trị tại địa chỉ mà nó trỏ đến
Kết quả:
```
main.c:14:11: error: assignment of read-only location '*ptrB'
   14 |     *ptrB = 8;
      |           ^
``` 
Nếu muốn thay đổi giá trị của A ta chỉ có thể thay đổi trực tiếp bằng biến theo cú pháp ```b = 8;``` thay cho ```*ptrB = 8;```
Kết quả: 
```
a = 10
b = 8
```
Con trỏ hằng vẫn có thể đổi địa chỉ trỏ đến khi muốn thay đổi.
Sử dụng con trỏ hằng khi không muốn đổi tượng của mình thay đổi giá trị (read only).

#### 4. Constant Pointer (Hằng con trỏ)
- Con trỏ chỉ trỏ đến một địa chỉ không thể thay đổi. Tức là sau khi khởi tạo sẽ không thể trỏ tới địa chỉ của con trỏ khác
- Cú pháp khai báo: ```int *const ptr = &a```
**Ví dụ:**
```cpp
#include <stdio.h>

int a = 20;
int b = 1;
int *const ptrA = &a;

int main(){
    ptrA = &b;
    printf("a = %d", *ptrA);
    return 0;

}
```
Vì  hằng con trỏ không thể thay đổi địa chỉ mà nó trỏ tới nên sẽ báo lỗi 
```
main.c:8:10: error: assignment of read-only variable 'ptrA'
    8 |     ptrA = &b;
      |          ^    
```

#### 5. NULL Pointer
- Khi khai báo con trỏ nhưng chưa sử dụng, mặc đinh cho giá trị con trỏ là NULL (0x00) để không trỏ tới địa chỉ khác. Hoặc sau khi sử dụng xong con trỏ thì gán NULL.
Cú pháp: ``` int *ptr = NULL;```

#### 6. Pointer to Pointer 
- Con trỏ cấp 1: ```*ptr = &a```
- Con trỏ cấp 2: ```**ptr1 = &ptr```
</details>

## Bài 6: BitMask  
<details><summary>Xem</summary>
 
- Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái. Có thể sử dụng bitmask để đặt, xóa và kiểm tra trạng thái của các bit cụ thể trong một từ (word).

- Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.

### Bitwise Operatiors
![Bitwise](https://i.imgur.com/HZs7vbg.png)
#### NOT: 
- 0 thành 1, 1 thành 0
- Cú pháp: ```~b``` 
#### AND:
- Khi tất cả intput bằng 1 thì output bằng 1, ngược lại bằng 0
- Cú pháp: ```a&b```
#### OR:
- Khi có ít nhất một input bằng 1 thì output bằng 1, ngược lại bằng 0
- Cú pháp: ```a|b```
### XOR:
- Khi có một ngõ vào khác các ngõ vào còn lại thì bằng 1, ngược lại bằng 0.
- Cú pháp: ```a^b```
#### Shift Left, Shift Right
- Dùng để di chuyển bit sang trái hoặc sang phải.
    - Trong trường hợp <<, các bit ở bên phải sẽ được dịch sang trái, và các bit trái cùng sẽ được đặt giá trị 0.
    - Trong trường hợp >>, các bit ở bên trái sẽ được dịch sang phải, và các bit phải cùng sẽ được đặt giá trị 0 hoặc 1 tùy thuộc vào giá trị của bit cao nhất (bit dấu).


**Ví dụ**
```cpp
#include <stdint.h>
#include <stdio.h>

int main(){

    const uint8_t init  = 0b01001011; // 75
    const uint8_t init1 = 0b01101001; // 105
    
    uint8_t notInit = ~init; //0b10110100: 180
    printf("NOT: %d\n", notInit);
    
    uint8_t AND = init&init1; //0b01001001: 73  
    printf("AND: %d\n", AND);

    uint8_t OR = init|init1; //0b01101011: 107
    printf("OR: %d\n", OR); 

    uint8_t XOR = init^init1; //0b00100010: 34
    printf("XOR: %d\n", XOR);

    uint8_t shiftLeft = init<<3; //0b01011000: 88
    printf("ShiftLeft 3 bit Init: %d\n", shiftLeft);

    uint8_t shiftRight = init>>4 ; //0b00000100: 4
    printf("ShiftRight 4 bit Init: %d\n", shiftRight);


    return 0;
}
```
Kết quả:
```
NOT: 180
AND: 73
OR: 107
XOR: 34
ShiftLeft 3 bit Init: 88
ShiftRight 4 bit Init: 4
```
**Ví dụ sử dụng bitmask**
```cpp
#define GENDER        1 << 0  //0000 0001
#define TSHIRT        1 << 1  //0000 0010
#define HAT           1 << 2  //0000 0100
#define SHOES         1 << 3  //0000 1000

#define FEATURE1      1 << 4  // Bit 4: Tính năng 1
#define FEATURE2      1 << 5  // Bit 5: Tính năng 2
#define FEATURE3      1 << 6  // Bit 6: Tính năng 3
#define FEATURE4      1 << 7  // Bit 7: Tính năng 4
```
Thay vì khai báo mỗi đối tượng với kiểu uint8_t sẽ mất 4 bytes thì ta chỉ cần khai báo 8 đối tượng mà chỉ mất 1 byte.
- Hàm bật một bit:
```cpp
void enableFeature(uint8_t *features, uint8_t change) {
    *features |= change;
}
```
- Giả sử ta có 
```
features:    10001000
change  :    00000100
______________________
features:    10001100
```
- Như ví dụ trên, ta chỉ cần bật bit 2 và sử dụng phép OR để khi ```feature|change``` thì bit tại vị trí cần bật lên sẽ luôn bằng 1. Và những bit tại ví trị khác của ```features``` OR với bit 0 của ```change``` sẽ luôn là chính nó (Không làm thay đổi các bit khác).

- Hàm tắt một bit:
```cpp
void disableFeature(uint8_t *features, uint8_t change) {
    *features &= ~change;
}
```
- Giả sử ta có  ```change: 00000010``` thì ```~change=11111101```
Kết quả:
```
features:    10001010
change  :    11111101
______________________
features:    10001000
```
Phép AND với 1 sẽ tắt bit của features tại vị trí bit 0 của change và các vị trí khác sẽ không đổi.

- Hàm đọc giá trị một bit
```cpp
int isFeatureEnabled(uint8_t features, uint8_t change) {
    return (features & change) != 0;
}
```
Giả sử ta muốn kiểm tra bit 5
```
features:    10001010
change  :    00100000
______________________
features:    00000000
```
Ta sẽ AND biến cần kiểm tra với mặt nạ mạng có giá trị 0 ở tất cả các bit (Kết quả luôn bằng 0) ngoại trừ vị trí cần kiểm tra sẽ có bit 1, nếu bit tại đó bằng 1 thì kết quả bằng 1, ngược lại bằng 0.
Cả hai hàm bật/tắt bit trên sẽ truyền vào con trỏ để xác định được vị trí đang lưu của đổi tượng cần thay đổi bit. Nhưng với hàm đọc chúng ta chỉ cần biết giá trị chứ không cần đổi nên sẽ truyền vào tham số là một biến bình thường. Lúc này, biến sẽ được khởi tạo ở một địa chỉ khác và không thay đổi giá trị của biến gốc.

Full Code:
```cpp
#include <stdio.h>
#include <stdint.h>


#define GENDER        1 << 0  // Bit 0: Giới tính (0 = Nữ, 1 = Nam)
#define TSHIRT        1 << 1  // Bit 1: Áo thun (0 = Không, 1 = Có)
#define HAT           1 << 2  // Bit 2: Nón (0 = Không, 1 = Có)
#define SHOES         1 << 3  // Bit 3: Giày (0 = Không, 1 = Có)
// Tự thêm tính năng khác
#define FEATURE1      1 << 4  // Bit 4: Tính năng 1
#define FEATURE2      1 << 5  // Bit 5: Tính năng 2
#define FEATURE3      1 << 6  // Bit 6: Tính năng 3
#define FEATURE4      1 << 7  // Bit 7: Tính năng 4

void enableFeature(uint8_t *features, uint8_t feature) {
    *features |= feature;
}

void disableFeature(uint8_t *features, uint8_t feature) {
    *features &= ~feature;
}


int isFeatureEnabled(uint8_t features, uint8_t feature) {
    return (features & feature) != 0;
}

void listSelectedFeatures(uint8_t features) {
    printf("Selected Features:\n");

    if (isFeatureEnabled(features, GENDER)) {
        printf("- Gender\n");
    }
    if (isFeatureEnabled(features, TSHIRT)) {
        printf("- T-Shirt\n");
    }
    if (isFeatureEnabled(features, HAT)) {
        printf("- Hat\n");
    }
    if (isFeatureEnabled(features, SHOES)) {
        printf("- Shoes\n");
    }
    printf("Feature Binary:\n");
    for (int i = 7; i >= 0 ; i--)
    {
        printf("%d", (features >> i) & 1);
    }
}

int main() {
    uint8_t options = 0;

    // Thêm tính năng 
    enableFeature(&options, GENDER | TSHIRT | HAT);

    disableFeature(&options, TSHIRT);

    // Liệt kê các tính năng đã chọn
    listSelectedFeatures(options);
    
    return 0;
}

```

Kết quả:
```
Selected Features:
- Gender
- Hat
Feature Binary:
00000101
```
Tại hàm main ta bật 3 bit ```GENDER | TSHIRT | HAT``` sau đó tắt một bit ```TSHIRT```, nên sẽ chỉ còn 2 bit được bật tại vị trí 0 và 2 như ta đã khai báo ở đầu.


</details>
    


















