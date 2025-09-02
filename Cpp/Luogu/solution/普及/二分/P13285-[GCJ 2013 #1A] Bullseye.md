# [GCJ 2013 #1A] Bullseye

## 题目描述

Maria 被 Ghastly Chemicals Junkies（GCJ）公司雇佣，帮助他们制造**靶心（bullseye）**。一个**靶心**由若干同心圆环（即圆心相同的圆环）组成，通常用作射箭靶。GCJ 只对黑白相间的靶心感兴趣。

![](https://cdn.luogu.com.cn/upload/image_hosting/dl5refc0.png)

Maria 拥有 $t$ 毫升的黑色油漆，她将用这些油漆绘制厚度为 $1\ \mathrm{cm}$（一厘米）的圆环。厚度为 $1\ \mathrm{cm}$ 的圆环指的是两个同心圆之间半径相差 $1\ \mathrm{cm}$ 的空间。

Maria 先在半径为 $r\ \mathrm{cm}$ 的白色圆外画上第一个黑色圆环。然后，只要油漆还够，她就不断重复如下过程：

1. Maria 想象在上一个黑色圆环外面有一个厚度为 $1\ \mathrm{cm}$ 的白色圆环。
2. 然后她在这个白色圆环外面再画一个厚度为 $1\ \mathrm{cm}$ 的黑色圆环。

注意，每一个“白色圆环”其实就是两条黑色圆环之间的空隙。

半径为 $1\ \mathrm{cm}$ 的圆盘面积是 $\pi\ \mathrm{cm}^2$。涂满面积为 $\pi\ \mathrm{cm}^2$ 需要 $1\ \mathrm{ml}$ 油漆。Maria 最多能画多少个黑色圆环？请注意：

* Maria 只会画完整的圆环。如果剩余油漆不足以画完整的黑色圆环，她会立即停止。
* 总会有足够的油漆画出至少一个黑色圆环。


## 说明/提示

**限制条件**

**小数据集（11 分，测试集 1 - 可见）**

- $1 \leq T \leq 1000$
- $1 \leq r, t \leq 1000$

**大数据集（13 分，测试集 2 - 隐藏）**

- $1 \leq T \leq 6000$
- $1 \leq r \leq 10^{18}$
- $1 \leq t \leq 2 \times 10^{18}$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
5
1 9
1 10
3 40
1 1000000000000000000
10000000000000000 1000000000000000000```

### 输出

```
Case #1: 1
Case #2: 2
Case #3: 3
Case #4: 707106780
Case #5: 49```

# 题解

## 作者：Lacuna (赞：2)

### 思路：

本以为非常简单，写了个暴力：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define gc getchar
#define pb push_back
#define ls u<<1
#define rs u<<1|1
const int ri=2e5+5;
template<typename T>inline void read(T&x){x=0;int f=1;char ch=gc();while(!isdigit(ch)){if(ch=='-') f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=gc();}x*=f;}
template<typename T,typename ...T1>inline void read(T&x,T1&...x1){read(x);read(x1...);}
int r,t,T,cnt,id=1;
void solve(int x){
	cnt=0;
	read(r,t);
    r++;
	while(t>0){
		t-=(r*r-(r-1)*(r-1));
		cnt++;
		r+=2;
	}
	if(t<0) cnt--;
	printf("Case #%lld: %lld\n",x,cnt);
}
signed main(){
	read(T);
    while(id<=T){
    	solve(id++);
	}
	return 0;
}
```

然而会 T。

考虑怎么优化。

一个一个减太费时间，看一下能不能 $O(1)$ 算 $k$ 个圆的面积。

题目中告诉我们：涂满面积为 $\pi\ \mathrm{cm}^2$ 需要 $1\ \mathrm{ml}$ 油漆。

所以我们可以直接省略 $\pi$。

先考虑第一个圆要用的油漆：

> $S_1 = ( r + 1 ) ^ 2 - r^2 = r^2 + 2r + 1 - r^2 = 2r + 1$

第二个圆用的油漆：

> $S_2 = (r + 3) ^ 2 - (r+2)^2=r^2+6r+9-r^2-4r-4=2r+5$

由此推出：

> $S_k=2r+(k-1) \times 4+1=2r+4k-3$

然后就可以等差数列算涂 $k$ 个圆要用的油漆。

> $S=(2r+1+2r+4k-3) \times  k \div 2=(2r+2k-1) \times k$

肯定不能一个一个试，发现这个东西满足单调性，所以二分这个 $k$，就做完了。

两个 $2^{18}$ 相乘，要开 ```__int128```。
 

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
#define gc getchar
#define pc putchar
#define pb push_back
#define ls u<<1
#define rs u<<1|1
const int ri=2e5+5;
template<typename T>inline void read(T&x){x=0;int f=1;char ch=gc();while(!isdigit(ch)){if(ch=='-') f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=gc();}x*=f;}
template<typename T,typename ...T1>inline void read(T&x,T1&...x1){read(x);read(x1...);}
int r,t,T,cnt,id=1,L,R;
int sum(int k,int r){
     return (2*r+2*k-1)*k;
}
void solve(long long x){
	cnt=0;
	read(r,t);
    L=0,R=2e18;
    while(L+1<R){
        int mid=L+R>>1;
        if(sum(mid,r)<=t){
            L=mid;
        }else{
            R=mid;
        }
    }
	printf("Case #%lld: %lld\n",x,L);
}
signed main(){
	read(T);
    while(id<=T){
    	solve(id++);
	}
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：1)

求 $t\text{ cm}^2$ 颜料可以画多少圈蚊香。

## 思路

对于第 $k$ 道黑圈，不难发现它的面积为 $[2(k-1)+r+1]^2-[2(k-1)+r]^2$。

拆解算试：
$$
\pi\times\{ [2(k-1)+r+1]^2-[2(k-1)+r]^2\}
\\=\pi\times\{[2k-1+r]^2-[2k-2+r]^2]\}
\\=\pi\times\{4k^2-4k+4kr+1-2r+r^2-(4k^2-8k+4kr+4-4r+r^2)\}
\\=\pi\times\{-4k+1-2r+8k-4+4r\}
\\=\pi\times\{4k-3+2r\}
$$

由于 $π\text{ cm}^2$ 用掉的油漆为 $1$，所以我们可以忽视 $\pi$。

要求 $k$ 个黑圈总和不大于 $t$，可以得到：

$$
\sum^k_{i=1}4i-3+2r\le t\\
=2(k+1)k-3k+2rk\le t\\
=2k^2+2k-3k+2rk\le t\\
=2k^2+(2r-1)k\le t
$$

我们就可以用二分的方法求得 $k$ 关于原式不大于 $t$ 的最大值。

### 关于右边界

左边界为 $1$ 因为题目中提到至少能画一个圈。右边界我们可以设为 $2^p$ 使 $2^{p+1}+(2r-1)2^p\le t$，这样可以大概圈出一个范围，又不会导致右边界溢出。

## 代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int r1,t;
bool solve(int mid){
    int ans=2*mid*mid+mid*(2*r1-1);
    return ans<=t;
}
signed main(){

    //2k^2 + (2r - 1)k
    int t1;
    cin>>t1;
    int q=t1;
    
    while(t1--){
        int ans=0;
        
        cin>>r1>>t;
        int l=1,r=1;
        while(solve(r))r*=2;
        while(l<=r){
            int mid=(l+r)/2;
            if(solve(mid)){
                ans=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        cout<<"Case #"<<q-t1<<": "<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：Xiaoshangjie (赞：0)

这是一篇充满数学味的题解。

### 题意
从一个半径为 $r\ {\rm cm}$ 的环开始，每次间隔 $1\ {\rm cm}$ 交替涂（不涂）色，当剩余的油漆 $t$ 少于下一次涂色的消耗时终止涂色。问：最多可以涂几次色？

### 思路
小学学过的知识：~~（还记得吗？）~~  
对于一个宽度为 $1$ 的圆环，其内必定包含一个半径为 $r$ 的圆，若将环内的圆与环视作整体，则可以得到一个半径为 $r+1$ 的圆，那么这个环的面积
$$
S=[(r+1)^2-r^2]\pi
$$
根据平方差公式 $a^2-b^2=(a+b)(a-b)$，可进一步简化环的面积
$$
S=[(r+1+r)(r+1-r)]\pi=(2r+1)\pi
$$

**下面我们进入正题。**

由题意，
- 第 $i$ 个被涂色的黑色圆环**内**半径为 $r+2(i-1)$。  
  为什么 $(i-1)$ 的系数是 $2$ 呢？因为中间跳过了白色圆环。当 $i=1$ 时，处于未涂色状态，自然内半径为 $r$。
- 第 $i$ 个被涂色的黑色圆环**外**半径为 $r+2(i-1)+1$。  
  这里不过多说明了，上面也有讲。

于是，我们可以求出第 $i$ 个被涂色的黑色圆环的面积
$$
S=[(r+2i-1)^2-(r+2i-2)^2]\pi=(2r+4i-3)\pi
$$
由于 $1\ {\rm ml}$ 油漆可以涂 $\pi\ {\rm cm^2}$ 的面积（题中有讲，数学也有学），所以第 $i$ 个黑色圆环需要 $(2r+4i-3)\ {\rm ml}$ 的油漆。

那么，前 $m$ 个黑色圆环的油漆耗费是
$$
\sum_{i=1}^{m}(2r+4i-3)=2m^2+(2r-1)m
$$
题目就转换成了：找到最大的正整数 $m$ 满足
$$
2m^2+(2r-1)m\le t
$$

该怎么实现呢？
1. 首先考虑**暴力枚举** $m$ 的值，但看到样例的 Case#4 时，最好还是知难而退，毕竟数据范围极大。
2. 再看一遍这句话：找到最大的正整数 $m$ 满足......这不是**二分**吗！？  
   那这是二分左答案，还是右答案呢？  
   显然是二分**左答案**，因为题目说：
   > 总会有足够的油漆画出至少一个黑色圆环。
   
   所以 $m=1$ 时一定可行。当满足条件时，我们`left=mid+1;`，否则`right=mid-1;`。注意：满足条件时，记得更新答案`ans=mid`。

于是，我们最终选择二分答案。  
问题来了：二分答案的右边界应当是多少？  
可以考虑 $10^9$。原因还是样例的 Case#4，数据非常极限，而它的答案小于 $10^9$。  
这样的话，一组数据的时间复杂度是 $O(\log{C})$，其中 $C$ 是值域（这里是 $10^9$）。那么总时间复杂度是 $O(T\log{C})$

**特别注意：**  
我们要使用`term1=2*mid*mid`和`term2=(2*r-1)*mid`分别计算两部分，再通过`term1<=t-term2`判断，防止溢出。

### code（？
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,r,t;
int main()
{
    cin>>T;
    for(int k=1;k<=T;k++)
    {
        cin>>r>>t;
        long long left=0,right=1e9,ans=0; 
        //二分查找最大的m，使得使用m个圆环的油漆量不超过t
        while(left<=right)
		{
            long long mid=(left+right)/2;
            long long term1=2*mid*mid;//term1对应公式中的2m^2部分
            long long term2=(2*r-1)*mid;//term2对应公式中的(2r-1)m部分
            
            // 检查使用m个圆环的总油漆量是否<=t
            if(term1<=t-term2)
			{
                ans=mid;//记录当前可行的m
                left=mid+1; 
            }
			else right=mid-1;//尝试更小的m
        }
        cout<<"Case #"<<k<<": "<<ans<<endl;
    }
    return 0;
}    
```

这就对了嘛？并不，你会发现 Subtask 1 WA 了，为什么？

让我们重新观察判定的不等式：
$$
2m^2+(2r-1)m\le t
$$
我们发现：当 $m$ 很大的时候，`long long`也存不下 ~~（不考虑`unsigned long long`）~~。考虑重新规划不等式，将 $2m^2$ 的 $m$ 提出，变成：
$$
(2m+2r-1)m\le t
$$
此时就不再涉及平方项，也就不会溢出。

下面贴上 AC 代码。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,r,t;  
int main()
{
    cin>>T;
    for(int k=1;k<=T;k++)
    {
        cin>>r>>t;
        long long left=0,right=1e9,ans=0;
        while (left<=right)
		{
            long long mid=(left+right)/2;
            long long term=2*mid+2*r-1; 
            //关键修复：避免乘法溢出，改用除法和取模检查
            //考虑双重检查，以防溢出
            bool valid=false;
            if (term>0) 
                if (mid<=t/term && mid*term<=t)
                    valid=true;
            
            if (valid)
			{
                ans=mid;      
                left=mid+1;
            }
			else right=mid-1;
        }
        cout<<"Case #"<<k<<": "<<ans<<endl; 
    }
    return 0;
}    
```

---

