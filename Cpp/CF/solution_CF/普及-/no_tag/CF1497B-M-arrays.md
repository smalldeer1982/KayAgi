# M-arrays

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ consisting of $ n $ positive integers and a positive integer $ m $ .

You should divide elements of this array into some arrays. You can order the elements in the new arrays as you want.

Let's call an array $ m $ -divisible if for each two adjacent numbers in the array (two numbers on the positions $ i $ and $ i+1 $ are called adjacent for each $ i $ ) their sum is divisible by $ m $ . An array of one element is $ m $ -divisible.

Find the smallest number of $ m $ -divisible arrays that $ a_1, a_2, \ldots, a_n $ is possible to divide into.

## 说明/提示

In the first test case we can divide the elements as follows:

- $ [4, 8] $ . It is a $ 4 $ -divisible array because $ 4+8 $ is divisible by $ 4 $ .
- $ [2, 6, 2] $ . It is a $ 4 $ -divisible array because $ 2+6 $ and $ 6+2 $ are divisible by $ 4 $ .
- $ [9] $ . It is a $ 4 $ -divisible array because it consists of one element.

## 样例 #1

### 输入

```
4
6 4
2 2 8 6 9 4
10 8
1 1 1 5 2 4 4 8 6 7
1 1
666
2 2
2 4```

### 输出

```
3
6
1
1```

# 题解

## 作者：江户川·萝卜 (赞：5)

因为只要相邻两个和为 $m$ 的**倍数**，先将每个数 $\bmod\ m$，不影响结果。

这时，每个数在 $[0,m)$ 区间内，两个数相加必 $\le 2(m-1)=2m-2$，也就是不能为 $2m$。所以只要考虑相加为 $m$ 即可。而相加为 $m$ 只有 $i+(m-i)=m$

接下来，用 $c_i$ 来记录多少数模 $m$ 后为 $i$，用 $\operatorname{ans}$ 来记录组数。

- 数组中所有 $m$ 的倍数只能放在一组，不然和哪个数相加都不是 $m$ 的倍数。所以当 $c_i$ 不为 $0$ 时，$\operatorname{ans}$ 加 $1$。

- 对于每一个 $i(1\le i\le \lfloor \dfrac x 2 \rfloor)$，设 $a=\max(c_i,c_{m-i}),b=\min(c_i,c_{m-i})$。
	- 如果 $a=0$ 且 $b=0$，不用分组。
   - 如果 $a=b$ 或者 $a=b+1$，两种数可以交替，这样相邻两个数之和均为 $m$ 的倍数。$\operatorname{ans}$ 加一。
   - 否则，将 $a-(b+1)$ 个数每一个单独分组，加上 $a=b+1$ 的部分，$\operatorname{ans}$ 共加 $1+a-b-1=a-b$ 个。
   
### Code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>.
using namespace std;
int c[100005];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		memset(c,0,sizeof(c));
		int n,m,val;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&val);
			c[val%m]++;
		}
		int ans=!!(c[0]);
		for(int i=1;i<=m/2;i++){
			int a=max(c[i],c[m-i]),b=min(c[i],c[m-i]);
			if(c[i]==0&&c[m-i]==0) continue;
			if(a==b||a==b+1) ans+=1;
			else ans+=1+(a-b-1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：NaOHqwq (赞：1)

## 题意

给定 $n$ 个数 $a_1,a_2,\dots,a_n$ 和一个整数 $m$，你需要将它们分成几个部分，使得每个部分当中，相邻两个数的和都能被 $m$ 整除。你可以将它们重新调换成你想要的顺序。求最少需要分成几个部分。

共有 $t$ 组数据，其中 $1\leqslant t\leqslant 1000,1\leqslant n,m\leqslant 10^5,1\leqslant a_i\leqslant 10^9$。

## 思路

做题之前一定要看数据范围。。

题目中的数据范围是 $1\leqslant t\leqslant 1000,1\leqslant n,m\leqslant 10^5,1\leqslant a_i\leqslant 10^9$，所以我们的每一次操作的复杂度至少要是线性的。

那么要如何做到线性呢？

题目中要求两数的和要能被 $m$ 整除，根据学过的取模相关知识，可得两数对 $m$ 取模的值也能被 $m$ 整除。可以在输入时直接对 $m$ 取模，再存入新数组。

那对于两数和等于 $m$ 的情况，则两数对 $m$ 取模的值之和等于 $m$。

这样一分析，就可以将复杂度降低啦。

详见代码 qwq。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005], b[100005];
int t, n, m;
int main(){
	cin >> t;
	while(t--){
		int ans = 0; //ans 变量为分出的组数
		memset(b, 0, sizeof(b)); //记得初始化
		cin >> n >> m;
		for(int i = 1;i <= n;i++){
			cin >> a[i];
			b[a[i]%m]++; //存入新数组
		}
		if(b[0]){ //余数为 0 则直接分出一部分
			ans++;
		}
		for(int i = 1;i <= m/2;i++){ //枚举到 m/2 就可以啦
			if(b[i]==0 && b[m-i] == 0){
				continue; //继续枚举下一个
			}
			if(abs(b[i]-b[m-i]) == 0){ //两数个数相同
				ans++; //直接分出一部分
			}else{
				ans += abs(b[i]-b[m-i]); //答案增加两数的差
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Silence_water (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1497B)

---

**Analyse**

当相邻两数的和能被 $m$ 整除时，两数模 $m$ 的和为 $0$ 或 $m$。

因此将序列中的每个数都对 $m$ 取模，用 $t$ 数组（桶）来记录一下取模后的数字出现的次数。

设取模后的数字为 $x$，且 $0\le x\le \lfloor \dfrac{m}{2}\rfloor$。设 $a=t[x]$，$b=t[m-x]$。

1. 当 $x=0$ 时，若 $t[0]> 0$，对答案的贡献为 $1$，否则为 $0$。

2. 当 $x=\dfrac{m}{2}$ 且 $m$ 为偶数时，若 $t[x]> 0$，对答案的贡献为 $1$，否则为 $0$。

3. 当 $a=b$ 时，对答案的贡献为 $1$。

4. 当 $a=0$ 时，对答案的贡献为 $b$。

5. 当 $b=0$ 时，对答案的贡献为 $a$。

6. 其余情况，对答案的贡献为 $\left|a-b\right|$。

对于情况 $6$ 的解释：不妨设 $a>b$，那么我们可以将 $b$ 个 $m-x$ 插在 $b+1$ 个 $x$ 之间。这样还剩下 $a-b-1$ 个 $x$ 需要一个数为一组，故总共为 $a-b$ 组。

---

**Solution**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+6;
int T,n,m,a[M],t[M];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(t,0,sizeof(t));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			t[x%m]++;
		}
		int ans=t[0]?1:0;
		for(int i=1;i<=m/2;i++)
		{
			if(i==m/2&&m/2==0)ans+=t[m/2]?1:0;
			else
			{
				int a=t[i],b=t[m-i];
				if(a==0||b==0||a!=b)ans+=abs(a-b);
				else ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

**The end**

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：liboxuan223 (赞：1)

### **题意：**
 $t$ 组数据，每组给定 $n$ 个数和一个整数 $m$。将它们分成几个部分，需使得每个部分当中，相邻两个数的和都能被 $m$ 整除。顺序可自己调整。求最少需要分成几个部分。


------------
### **思路**
看一下数据范围，$n$ 最大会到 $1 \times 10^5$，循环嵌套肯定不行，优化一下，可以运用一下桶的思想，可以在输入时输入一个数 $x$ 然后直接 $x \bmod m$，再存入新数组，再将下标从 $1$ 枚举到 $m \div 2$ 判断数组中下标为 $i$ 与 $m - i$ 的值是否符合条件，再进行累加操作就完成了。

**代码如下：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 10;

int a[N], tt[N];

int n, m;
int t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t --){
		int ans = 0;//记录一共分了几组
		memset(tt,0,sizeof tt);
		cin >> n >> m;
		for(int i = 1;i <= n; i ++){
			cin >> a[i];
			tt[a[i] % m] ++;//存入新数组，进行“桶”化
		}
		if(tt[0]) ans ++;//余数为0，直接新开一组
		for(int i = 1;i <= m / 2; i ++){
			if(tt[i] == 0&&tt[m - i] == 0){
				continue;//直接跳过，枚举下一个
			}
			if(abs(tt[i] - tt[m - i]) == 0){
				ans ++;//个数相同，刚好匹配，新开一组
			}else{
				ans += abs(tt[i] - tt[m - i]);//个数不同，则增加两数的差
			}
		}
		cout << ans << '\n';
	}
	
	return 0;
}
``````

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1497B)

想让两个数的和能整除 $m$，就要让两个数取余 $m$ 的和能整除 $m$。

所以我们使用桶标记，记录有几个数取 $m$ 等于 $i$，存在数组 $cnt_i$ 里。

再枚举到 $\frac{m}{2}$，判断 $i$ 和与之互补的 $m-i$ 满足什么条件，将答案累加即可。

注意每次都要清空数据。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a,cnt[100010],ans;
int main(){
	cin>>t;
	while(t--)
	{
		ans=0;
		memset(cnt,0,sizeof(cnt));
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			cnt[a%m]++;
		}
		if(cnt[0])//特判0的情况
			ans++;
		for(int i=1;i<=m/2;i++)
		{
			if(cnt[i]==0&&cnt[m-i]==0)//互相匹配的都没有数量
			{ 
				continue;
			}
			if(abs(cnt[i]-cnt[m-i])==0)//刚好匹配完
			{
				ans++; 
			}
			else//其他
			{
				ans+=abs(cnt[i]-cnt[m-i]); 
			}
		}
		cout<<ans<<endl;
	}
	return 0;
} 
 
```


---

## 作者：Leap_Frog (赞：0)

### P.S.
![](https://cdn.luogu.com.cn/upload/image_hosting/uez1hrig.png)  
$\uparrow$ 被 div.2 B 搞自闭的 xtw $\uparrow$

### Solution.
首先，$\mod m$ 同余的数在这题中本质一样。  
所以我们可以按照 $\mod m$ 指开桶。  
首先，$\mod m$ 为 $0$ 的如果有只需要一个序列。  
同时 $\mod m$ 等于 $\frac m2$ 的也只需要一个序列。  
然后处理 $x$ 和 $m-x$，设其中较小出现次数为 $a$，较大出现次数为 $b$。  
那答案就是 $[a\not=0]\times\max\{1,b-a\}$，证明就是考虑较小的可以带 $a+1$ 个数。  
然后就做完了，不要问 xtw 为什么会罚三次时 ![](//xn--9zr.tk/xk)  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
int Ca,n,m,a[100005],cnt[100005];
inline void solve()
{
	read(n),read(m);for(int i=1;i<=n;i++) read(a[i]);
	int res=0;for(int i=1;i<=n;i++) cnt[a[i]%m]++;
	if(cnt[0]) res++,cnt[0]=0;
	for(int i=1;i<=m/2;i++)
	{
		int a=cnt[i],b=cnt[m-i];if(a>b) swap(a,b);
		if(!a&&!b);else if(a==b||a+1==b) res++;else res+=b-a;
	}
	printf("%d\n",res);for(int i=1;i<=n;i++) cnt[a[i]%m]=0;
}
int main() {for(read(Ca);Ca--;) solve();return 0;}
```

---

## 作者：Laisira (赞：0)

### 题面
给定一个长 $n$ 的序列和 $m$，求最少分为几组，使得每一组中相邻元素和为 $m$ 的倍数，$t$ 组询问。

### 思路
先把每个数和 $m$ 的余数搞出来，对于余数为 $i$ 的个数为 $e_i$。枚举 $i$，他的相邻数只能是 $m-i$。

分类讨论：
- $e_i=0$ 且 $e_{m-i}=0$ 时不用管。
- $e_i=e_{m-i}$ 或 $e_i=e_{m-i}\pm 1$ 时可以分为一组。
- 否则需要 $\min(|e_{m-i}-e_i\pm 1|)+1$ 组。

### 代码
```cpp
    #include<bits/stdc++.h>
    #define Maxn 100005  
    using namespace std;
    int e[Maxn];
    int main()
    {
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        int t,n,m;
        cin>>t;
        while(t--) {
            cin>>n>>m;
            memset(e,0,sizeof(e));
            for(int i=1;i<=n;i++) {
                int u;
                cin>>u;
                e[u%m]++;
            } int ans=!!(e[0]);
            for(int i=1;i<=(m>>1);i++) {
                if(!e[i]&&!e[m-i])continue;
                if(e[i]==e[m-i]||abs(e[i]-e[m-i])==1)
                    ans++;
                else ans+=abs(e[i]-e[m-i]);
            } cout<<ans<<"\n";
        }
        return 0;
    }
```

---

## 作者：Storm_Lightning (赞：0)

# CF1497B M-arrays

## 题目大意

给你 $n$ 个数和一个数 $m$，使得经过分组后每组里面相邻两数之和可以整除 $m$，求最少分几个部分。

## 思路分析

我们知道定理 $a \equiv a-b \pmod b$，所以我们可以选择开一个桶 $k$，来记录 $a \bmod b$ 的个数，下来就得分情况讨论一下。

- $k[0] \ge 1$ 的时候，我们就只能让这些数分为一组，$ans+1$。

- $k[i]==k[m-i]$ 并且 $k[i]==0$ 直接跳过即可。

- $k[i]==k[m-i]$ 我们也可以使得这些数分为一组，$ans+1$。

- 最后一种情况，让 $ans + |b[i]-b[m-i]|$ 即可。

### 注意事项

- for 循环是从 $1$ 到 $m/2$。

- 记得加上绝对值。

- 桶记得要清空。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a,ans;
int k[100010];
signed main()
{
	cin>>t;
	while(t--)
	{
		memset(k,0,sizeof(k));
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			k[a%m]++;
		}
		if(k[0]!=0) ans++;
		for(int i=1;i<=m/2;i++)
		{
			if(k[i]==k[m-i]&&k[i]==0) continue;
			if(k[i]==k[m-i])ans++;
			else ans+=abs(k[i]-k[m-i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Wind_Smiled (赞：0)

## 题意

给定 $n$ 个数 $a_1,a_2,\dots,a_n$ 和一个整数 $m$，你需要将它们分成几个部分，使得每个部分当中，相邻两个数的和都能被 $m$ 整除。你可以将它们重新调换成你想要的顺序。求最少需要分成几个部分。

$T$ 组数据，$1 \le T \le 10^3$，$1 \le n,m \le 10^5$，$1 \le a_i \le 10^9$。

## 分析

数据约定，对于每一次查询，必是线性或更低级别的复杂度。

既然是和可以被 $m$ 整除，那两数对于 $m$ 取模之后的值也必定会被 $m$ 整除。所以我们可以在读入的时候把这个数据 $\bmod m$ ，并且存入余数数组。

我们可以考虑，对于两个数的和等于 $m$ 的情况，必定是这两个数除以 $m$ 的余数之和等于 $m$。所以考虑余数互补。

我们每一组查询，循环到 $\dfrac{m}{2}$  即可。然后判断第 $i$ 位以及互补的 $m-i$ 位满足什么条件，累加答案即可，在最开始记得清空答案即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a,mod[100005],ans;
int main(){
	scanf("%d",&t);
	while(t--){
		ans=0;
		memset(mod,0,sizeof(mod));//清空数据 
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a);
			mod[a%m]++;
		}
		if(mod[0]){//若余数为 0 则分出一部分
			ans++;
		}
		for(int i=1;i<=m/2;i++){
			if(mod[i]==0&&mod[m-i]==0){//如果都为 0 则退回枚举下一个 
				continue;
			}
			if(abs(mod[i]-mod[m-i])==0){//两种数个数相等 
				ans++;//分出一个部分即可 
			}
			else{//其他情况就是不相等 
				ans+=abs(mod[i]-mod[m-i]);//答案要增加它们的差值 
			}
		}
		printf("%d\n",ans);//输出 
	}
	return 0;
}
```
复杂度确实为线性，可以通过此题。

---

