# Forgetting Things

## 题目描述

### 题意简述

求不定方程

$$a+1=b$$

且 $a$ 的第一位为 $d_a$，$b$ 的第一位为 $d_b$ 的一组解。

## 样例 #1

### 输入

```
1 2
```

### 输出

```
199 200
```

## 样例 #2

### 输入

```
4 4
```

### 输出

```
412 413
```

## 样例 #3

### 输入

```
5 7
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
6 2
```

### 输出

```
-1
```

# 题解

## 作者：fengqiao17 (赞：2)

## Solution
分析题意，这道题有四种情况：

1. $d_a+1=d_b$，那么有 $a=\overline{d_a9}$，$b=\overline{d_b0}$；

2. $d_a=d_b$，那么有 $a=\overline{d_a0}$，$b=\overline{d_b1}$；

3. $d_a=9$，$d_b=1$，那么有 $a=9$，$b=10$；

4. 其他情况输出 $-1$。

------------

## Code

```cpp
//author:fengqiao17
//转载请标明地址：https://616673.blog.luogu.org/solution-cf1225a
#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b;
  cin >> a >> b;
  if (a + 1 == b) //第一种情况
    cout << b * 10 - 1 << " " << b * 10 << endl;
  else if (a == b) //第二种情况
    cout << a * 10 << " " << a * 10 + 1 << endl;
  else if (a == 9 && b == 1) //第三种情况
    cout << "9 10" << endl;
  else //第四种情况
    cout << -1 << endl;
  return 0;//完结撒花
}
```

---

## 作者：JustinXiaoJunyang (赞：2)

思路分析：

我们直接构造：

- $d_a=9,d_b=1$ 则 $a=9,b=10$。

- $d_a+1=d_b$ 则 $a=\overline{d_a9},b=\overline{d_b0}$。

- $d_a=d_b$ 则 $a=\overline{d_a0},b=\overline{d_b1}$。

没有其他情况了，无解就输出 $-1$。

参考代码：

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a,b;
    cin >> a >> b;
    if (a == 9 && b == 1) cout << "9 10" << endl;
    else if (a + 1 == b) cout << b * 10 - 1 << " " << b * 10 << endl;
    else if (a == b) cout << a * 10 << " " << a * 10 + 1 << endl;
    else cout << -1 << endl;
    return 0;
}
```

---

## 作者：Meatherm (赞：2)

如果有解，那么只有三种情况：

1. $d_a=d_b$。我们可以考虑构造 $\overline{d_a1},\overline{d_a2}$ 这两个数。

2. $d_a=d_b-1$。我们可以考虑构造 $\overline{d_a9},\overline{d_b0}$ 这两个数。

3. $d_a=9,d_b=1$。我们可以考虑构造 $999,1000$ 这两个数。

当然上述构造方法并不唯一。

```cpp
# include <bits/stdc++.h>
# define rr register
int a,b;
int main(void){
	scanf("%d%d",&a,&b);
	if(b-a!=0&&b-a!=1&&!(a==9&&b==1)){
		printf("-1");
	}
	if(b-a==1){
		printf("%d9 %d0",a,b);
		return 0;
	}
	if(b-a==0){
		printf("%d1 %d2",a,b);
	}
	if(a==9&&b==1){
		printf("%d99 %d000",a,b);
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题只需要我们用到分类讨论的思想即可。首先我们会发现大多数的 $a+1$ 是不会进位的那么这种情况就要是 $d_a$ 与 $d_b$ 相等才行，但是也有一些特殊情况会进位且有解就只有可能是 $d_a=d_b-1$ 如样例 $1$ 这样 $a$ 就一定为 $n$ 个 $9$ 结尾那么 $b$ 就为 $n$ 个 $0$ 结尾，还有种情况就是 $d_a=9$ 且 $d_b=1$ 那么输出 $9$ 和 $10$ 即可，若不符合上述情况则无解。
# AC代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
int a,b;
int main() {
	cin>>a>>b;
	if(a==9&&b==1) return cout<<"9 10",0; // 特判
	if(a-b==-1) {
		cout<<a<<"99 "<<b<<"00"; //要进位
	} else if(a==b) cout<<a<<"00 "<<b<<"01";//不进位
	else cout<<"-1"; // 无解
	return false; // 完结散花
} 
```


---

## 作者：hyc1026 (赞：0)

本题题意清晰，无需解释。

建议评红。

------------

有解：

1. $d_a=d_b$，构造 $a=\overline{d_a0},b=\overline{d_b1}$。

1. $d_a+1=d_b$，构造 $a=\overline{d_a9},b=\overline{d_b0}$。

1. $d_a=9,d_b=1$，构造 $a=9,b=10$。

假如全不满足以上条件，则说明无解，输出 $-1$。

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a,b;
    cin >> a >> b;
    if(a == b) cout << a*10 << " " << a*10+1 << endl; //情况1
    else if(a + 1 == b) cout << b*10-1 << " " << b*10 << endl; //情况2，此时b*10-1与a*10+9等同
    else if(a == 9 && b == 1) cout << "9 10" << endl; //情况3
    else cout << -1 << endl; //无解
    return 0;
}
```

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题其实考察就是分类讨论的细致性，依题意，可分为如下三种情况：

1. $d_{a}=d_{b}$，那么只需随机找两个首位为 $d_{a}$ 的数即可。

1. $d_{a}=d_{b}-1$，那么只需找到 $d_{a} \times 100+99,d_{b} \times 100$ 这两个数即可。

1. 最特殊的一种情况就是 $d_{a}=9,d_{b}=1$，则可以找到 $999,1000$ 两个数。

1. 若不是上面任何一种，输出 $-1$

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	if(a==b)
	{
		cout<<a*100+1<<" "<<b*100+2;
	}
	else if(a==b-1)
	{
		cout<<a*100+99<<" "<<b*100;
	}
	else if(a==9&&b==1)cout<<999<<" "<<1000;
	else cout<<"-1";
	return 0;
}

```

谢谢观看

---

## 作者：DepletedPrism (赞：0)

题意简述: 

给定两数 $a,\ b$ 的第一个数字 $d_a,\ d_b$ 构造 $a,\ b$ 使其满足 $a+1 = b$

-------

~~考虑到只有 81 种情况, 我们使用暴力~~

经过思考可以发现, $d_a,\ d_b$ 取值大致分以下几种情况

- $d_a < d_b$

  - $d_a + 1 = d_b$, 此时输出 $d_a,\ d_b$ 即可
  - 若 $d_b - d_a > 1$, 即便有进位也无法使其满足, 此时无解
 

- $d_a = d_b$
  - 构造十位分别为 $d_a,\ d_b$, 个位为任意两个相差 $1$ 的数即可

- $d_a > d_b$
  - 考虑进位, 可以发现当且仅当 $d_a = 9,\ d_b = 1$ 时能构造出 $9 + 1 = 10$, 其余情况无解

属于比较容易分类讨论的题了

-----
  
代码

```cpp
// CF A
// DeP
#include <cstdio>
 
int a, b;
 
int main() {
    scanf("%d%d", &a, &b);
    if (a + 1 == b) printf("%d %d\n", a, b);
    else if (a == 9 && b == 1) printf("%d %d\n", 9, 10);
    else if (a == b) printf("%d %d\n", a * 10, b * 10 + 1);
    else printf("-1\n");
    return 0;
}
```

---

## 作者：傅思维666 (赞：0)


## 题解：

题目翻译人赶来发布第一篇题解。

~~CF​本场本题被hack了？~~

是一道分类讨论的题目。

用草纸模拟一下，我们发现题意有这么几个性质：

首先，假如$d_b>d_a+1$，那么肯定是满足不了性质的。

然后，假如$d_b<d_a$，也肯定满足不了性质。注意，特殊地：如果$d_a=1,d_b=9$，那么也可以满足性质，所以这样的情况被抛弃了。

因为是SPJ。所以剩下的情况随便判一判就好了。

注意细节一定要考虑全面。

比如那组hack数据：9 9

我一开始就没考虑到，导致hack成功。

所以加了个补丁。就过了（我太菜了）

```cpp
#include<cstdio>
using namespace std;
int da,db;
int main()
{
    scanf("%d%d",&da,&db);
    if(db>da+1 || (db<da && da!=9))
    {
        printf("-1");
        return 0;
    }
    else if(da==9 && db==9)
    {
        printf("91 92");
        return 0;
    }
    else if(da==9 && db!=1)
    {
        printf("-1");
        return 0;
    }
    else if(da==9 && db==1)
    {
        printf("9 10");
        return 0;
    }
    else if(da+1==db)
    {
        printf("%d %d",da,db);
        return 0;
    }
    else
    {
        printf("%d %d",da*10+1,db*10+2);
        return 0;
    }
}
```



---

