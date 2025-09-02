# Who's Opposite?

## 题目描述

Some number of people (this number is even) have stood in a circle. The people stand in the circle evenly. They are numbered clockwise starting from a person with the number $ 1 $ . Each person is looking through the circle's center at the opposite person.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560B/a3a7851777ae33a1527beddaa8761afd1adfcbd6.png)A sample of a circle of $ 6 $ persons. The orange arrows indicate who is looking at whom.You don't know the exact number of people standing in the circle (but this number is even, no doubt). It is known that the person with the number $ a $ is looking at the person with the number $ b $ (and vice versa, of course). What is the number associated with a person being looked at by the person with the number $ c $ ? If, for the specified $ a $ , $ b $ , and $ c $ , no such circle exists, output -1.

## 说明/提示

In the first test case, there's a desired circle of $ 8 $ people. The person with the number $ 6 $ will look at the person with the number $ 2 $ and the person with the number $ 8 $ will look at the person with the number $ 4 $ .

In the second test case, there's no circle meeting the conditions. If the person with the number $ 2 $ is looking at the person with the number $ 3 $ , the circle consists of $ 2 $ people because these persons are neighbors. But, in this case, they must have the numbers $ 1 $ and $ 2 $ , but it doesn't meet the problem's conditions.

In the third test case, the only circle with the persons with the numbers $ 2 $ and $ 4 $ looking at each other consists of $ 4 $ people. Therefore, the person with the number $ 10 $ doesn't occur in the circle.

## 样例 #1

### 输入

```
7
6 2 4
2 3 1
2 4 10
5 3 4
1 3 2
2 5 4
4 3 2```

### 输出

```
8
-1
-1
-1
4
1
-1```

# 题解

## 作者：ARGV (赞：5)

对与每次输入的 $a,b,c$ ，易得 $(a-b)×2$ 为总人数，那什么时候输出 -1 呢 ？ 当且仅当 $a,b,c$ 其中至少一个数大于总人数（因为编号从 1 开始）的时候才输出 -1 ，代码根据思路模拟即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
 
int main(){ 
	int n;
	cin>>n;
	int a,b,c;
	while(n>=1){
		cin>>a>>b>>c;
		if(abs(a-b)*2<max(a,b)||abs(a-b)*2<c){
			cout<<-1<<endl;
		}
		else{
			if(abs(a-b)+c>abs(a-b)*2)cout<<c-abs(a-b))<<endl;
			else cout<<c+abs(a-b)<<endl;
		}
		n--;
	}
    return 0;
} 
```

---

## 作者：Chinshyo (赞：1)

## 思路
我们可以通过 $a$ 和 $b$ 或任意两个相对面人的编号求出圈内的人的个数。

我们可以试着画图找规律。

![](https://cdn.luogu.com.cn/upload/image_hosting/kkryhknr.png)

从图中可发现：
- $i$ 和 $j$ 上面的数字个数为 $j-i+1$ ，而由于他们两两看着对方， $i$ 和 $j$ 下面的数字个数也为 $j-i+1$ 。因此圈内人数 $n$ 为 $2 + 2(b - a - 1)$ 。
- 每两个相互对视的人编号差为 $\dfrac{n}{2}$ 。

因此我们只需知道 $c$ ，解就是 $(c+\dfrac{n}{2})\mod n $ 。但如果计算得 0 ，则输出 $n$ 。

对于 $a$ ，$b$ 和 $c$ ， 如果其中任何一个不在 $n$ 的范围内，就无解，输出 `-1` 。这一结论亦通过找规律可得。

## 代码

```cpp
#include<bits/stdc++.h>
#define debug cout << "Helloworld" << endl
using namespace std;

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int a, b, c;
		cin >> a >> b >> c; 
		if(b < a) swap(a, b); //维持 b > a
		int n = 2 + (b - a - 1) * 2;
		if(n < max(a, max(b, c))) cout << -1 << endl;
		else if((c + n / 2) % n == 0) cout << n << endl;
		else cout << (c + n / 2) % n << endl;
	}
	return 0;
}

```


---

## 作者：happy_dengziyue (赞：1)

### 1 思路

设圆的周长为 $n$，我们可以得到一个公式：

$$n=\left|a-b\right|\times2$$

所以，如果：

$$a>n\operatorname{or}b>n\operatorname{or}c>n$$

就输出 `-1`。

否则，设答案为 $ans$，则：

$$ans=(c+n\div2)\bmod n$$

但注意特判 $ans=0$ 的情况，此时应该是 $ans=n$。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
int a,b,c;
int n;
int ans;
inline int absi(int a){
	return a>0?a:-a;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1560B_1.in","r",stdin);
	freopen("CF1560B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1;ca<=t;++ca){
		scanf("%d%d%d",&a,&b,&c);
		n=absi(a-b)*2;
		if(a>n||b>n||c>n){
			printf("-1\n");
			continue;
		}
		ans=(c+n/2)%n;
		if(ans==0)printf("%d\n",n);
		else printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56326916)

By **dengziyue**

---

## 作者：miserExist (赞：1)

## 题意
每次给三个数 $a$，$b$，$c$ ，表示在一个由一些点组成的圆环上(点的数量为偶数)，$a$ 号点与 $b$ 号点相对时，$c$ 号点对应的点的编号是多少，如果不存在输出 $-1$。
## 思路
一眼找规律模拟题。

点的数量最少为 $4$ ，当点的数量为 $4$ 时，$1$ 对应的点应该为 $3$。
![](https://z3.ax1x.com/2021/08/19/f75Qts.png)
并且每当 $1$ 所对应的点增加 $1$ 时，整张图点的数量就会增加 $2$。
![](https://z3.ax1x.com/2021/08/19/f75yjK.png)
所以整张图的点数 $u$ 满足：
$$
u = 4 + (b - 3) \times 2
$$
其中 $b$ 为这张图中 $1$ 号点对应的点的编号。

细节在代码注释中。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int N = 1e6 + 10;

int n,m;

signed main(){
    int ttt;
    cin >> ttt;

    while(ttt --)
    {
        int a,b,c;
        cin >> a >> b >> c;
        int t1 = a;
        int t2 = b;
        a = min(a,b), b = max(t1,b);
	
    	if(a != 1)//根据a和b求这张图1和其对应点
		{
	    	int temp = (a - 1);
    
	    	a = 1, b -= temp;//距离1的距离
		}
	
        if(b < 3)//不存在点数小于4的图
        {
            puts("-1");
            continue;
        }

        int u = 4 + (b - 3) * 2;
        if(c > u || t1 > u || t2 > u )//编号不能比图点数大
        {
            puts("-1");
            continue;
        }
        int v = u / 2;//双指针(?)
        
        //下面时寻找所求点在编号前半部分还是后半部分
        if(c <= v)//是前半部分的点 输出后半部分的对应点
        {
            cout << (u - (v - c)) << endl;
        }
        else //是后半部分的点 输出前半部分的对应点
        {
            cout << v - (u - c) << endl;
        }
        
    }
    
    return 0;
}
    
    
    
    
    
    
    
    
    


```

---

## 作者：luckydrawbox (赞：0)

## 题意

$2k$ 个人排成一个圈，编号依次为 $1,2,3,…,2k$，每个人可以透过圆心看到对面的人。

如在下图中，$1$ 可以看到 $4$，$5$ 可以看到 $2$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560B/a3a7851777ae33a1527beddaa8761afd1adfcbd6.png)

已知 $a$ 可以看到 $b$，问 $c$ 可以看到谁？若无解输出 $-1$。

## 分析

分析题目的例子可以发现，$|1-4|=3=k,|5-2|=3=k$，也就是说 $|a-b|=k$，这样我们就可以求出圈内人的最大编号 $2k$，如果 $a,b,c$ 中某一个大于 $2k$，显然无解。

若有解，则 $c$ 可以看到的人是 $c+k$，如果溢出就对 $2k$ 取模。

注意一下细节。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t,a,b,c,k;
int main()
{
    t=read();
    while(t--){
    	a=read();b=read();c=read();
    	k=abs(a-b);
    	if(a>2*k||b>2*k||c>2*k){//无解
    		cout<<-1<<endl;
    		continue;
		}
    	int ans=c+k;
    	if(c+k>2*k)//溢出就取模
    		ans%=2*k;
    	cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：OnlyExtreme (赞：0)

## 题意简述
一群人平均地围着一张圆桌，编号从 $1$ 到 $n$ 顺时针排列，保证 $n$ 为偶数。圆的直径两端的两个人被称为“相对的两个人”。在 $n$ 未知的情况下，告诉你 $a$ 与 $b$ 相对，求与 $c$ 相对的人的编号。

## 思路整理
我们看 $n=6$ 的情况。$1$ 与 $4$ 相对， $2$ 与 $5$ 相对， $3$ 与 $6$ 相对，我们会发现相对的两个人编号之差为二分之 $n$ ，也就是设 $a$ 与 $b$ 相对（$a > b$），共有 $n$ 个人，则有 $(a-b)\times2=n$ 。那么我们就可以通过 $a$ 和 $b$ 求出 $n$ 。只要 $a$，$b$，$c$ 中有一个超过 $n$ 则当前情况不成立。将上述性质应用于 $c$ 即可求出答案。

AC 代码如下。
```cpp
#include <bits/stdc++.h>
using namespace std;
 
// 注意要开 long long
long long t, a, b, c;
long long n;
 
int main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld %lld %lld", &a, &b, &c);
		if (a > b) swap(a, b); // 保证 a < b
		n = 1ll * (b - a) * 2; // 求出 n
		if (a > n || b > n || c > n) printf("-1\n"); // 错误判断
		else {
			// 利用性质求出答案
			if (c > n / 2) printf("%d\n", 1ll * c - n / 2);
			else if (c < n / 2) printf("%lld\n", 1ll * n / 2 + c);
			else printf("%lld\n", n);
		}
	}
	return 0;
}
```


---

