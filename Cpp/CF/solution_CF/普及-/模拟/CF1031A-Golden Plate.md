# Golden Plate

## 题目描述

You have a plate and you want to add some gilding to it. The plate is a rectangle that we split into $ w\times h $ cells. There should be $ k $ gilded rings, the first one should go along the edge of the plate, the second one — $ 2 $ cells away from the edge and so on. Each ring has a width of $ 1 $ cell. Formally, the $ i $ -th of these rings should consist of all bordering cells on the inner rectangle of size $ (w - 4(i - 1))\times(h - 4(i - 1)) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/347cd2ee781d01fc5a8212010a9a488ef250ad46.png)The picture corresponds to the third example.Your task is to compute the number of cells to be gilded.

## 说明/提示

The first example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/8ef68100f0e4d74d121ee779a666ca2b2a0d0fdf.png)The second example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/22b59cf41d139cb0bc1ae7e108eb90b4ef24521f.png)The third example is shown in the problem description.

## 样例 #1

### 输入

```
3 3 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
7 9 1
```

### 输出

```
28
```

## 样例 #3

### 输入

```
7 9 2
```

### 输出

```
40
```

# 题解

## 作者：Alex_Wei (赞：5)

因为数据范围极小 $(3≤w,h≤100)$ ，所以模拟即可，就连公式都给你了

$$i_{th}\ ring:(w-4(i-1))(h-4(i-1))$$

那么长就是

$$i_{th}:w-4(i-1)-1$$

宽就是

$$i_{th}:h-4(i-1)-1$$

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h,k,ans; 
int main()
{
	cin>>w>>h>>k;
	for(int i=1;i<=k;i++)
		ans+=2*(w-4*(i-1)-1+h-4*(i-1)-1);
	//长宽记得*2
	cout<<ans;
	return 0;
}
```

那么如果数据很大，也可以直接用等差数列求和公式 $O(1)$ 计算

$$2*\sum_{i=1}^{k}(w-4(i-1)-1)+(h-4(i-1)-1)$$

$$2*\sum_{i=1}^{k}w+h-8(i-1)-2$$

$$2*\sum_{i=1}^{k}w+h-8i+6$$

$$2*((w+h-8+6)+(w+h-8k+6))*k/2$$

$$k(2w+2h-8k+4)$$

$$2k(w+h-4k+2)$$

最后附上只有 $83B$ 的~~超短压行~~代码

```cpp
#include<iostream>
int w,h,k;main(){std::cin>>w>>h>>k,std::cout<<2*k*(w+h-4*k+2);}
```

求赞qwq

---

## 作者：REAL_曼巴 (赞：1)

此题的公式告诉你了，第 $i$ 中心层的大小为：
$ (w - 4(i - 1))\times(h - 4(i - 1)) $ 

我们可以用 $k$ 次循环来求解。（因数据过小）

此题还有不用循环的方法，就是使用等差数列求和来推一个更简单的公式，如下：$2k(w+h+2-4k)$

```
#include<cstdio>
using namespace std;
int main(){
    int w,h,k;
    scanf("%d%d%d",&w,&h,&k);
    printf("%d",(w+h+2-4*k)*2*k);
    return 0;
}
```


---

## 作者：Autism_ever (赞：1)

### 本题目比较水，规律都给你了
## 第i个中心面积：(w−4(i−1))×(h−4(i−1))
### 模拟一下就可以了
## 上代码！！
```cpp
#include<bits/stdc++.h>
using namespace std;
int w, h, k, cnt;
int main()
{
	cin>>w>>h>>k;
	for(int i=1;i<=k;i++)//循环找规律 
   	{
    	    cnt+=2*(w-8*i+6+h);//按照上面的公式推出来的
    	}
	cout<<cnt<<endl;//最后输出 
	return 0; 
}
```



------------
**~~为了防抄袭，所以输入输出必须用c语言的输入，输出，否则......~~**


---

## 作者：Xdl_rp (赞：0)


这道题挺水的，连算式都给了：



$(w-4 \times (i-1) ) \times (h - 4 \times (i - 1))$
        
所以直接套算式即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int w, h, k, ans = 0; //一堆变量
	cin >> w >> h >> k;//输入
	for (int i = 1; i <= k; i++) ans += 2 * (w - 4 * (i - 1) - 1 + h - 4 * (i - 1) - 1);//最重要的部分
	cout << ans;//输出
	return 0;
}
```


---

## 作者：zmza (赞：0)

这题是数学题。

推导出来的公式是：
$$2k(w+h+2-4k)$$

直接上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h,k;
int main()
{
    scanf("%d%d%d",&w,&h,&k);
    printf("%d",(w + h + 2 - 4 * k) * 2 * k);//面积
    return 0;
}
```


---

