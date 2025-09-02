# Basketball Team

## 题目描述

### 题面背景

作为德国开罗一所大学（简称 GUC ）的一名学生，瓦法同时也是一名篮球运动员。当听到 GUC 终于入围了一年一度的篮球比赛 （简称 ABC ）时，他十分高兴。

&nbsp;

### 题面描述

一个篮球队由 $n$ 名 GUC 的球员组成，但是团队中可能有来自不同学系的学生。 GUC 有 $m$ 个学系，编号从 $1$ 到 $m$ ，瓦法的学系编号为 $h$ 。对于学系 $i$， 已知 $s_i$ ，意思是学系 $i$ 中，有多少个打篮球的学生。

瓦法有特殊能力，使他一定能在篮球队中占一席之地。但是由于他讨厌浮点数，所以他需要你帮助他计算篮球队中至少有一个队友与他同一个学系的可能性。

**注意：我们认为每一个包含瓦法的团队出现的概率相同，每个学生彼此不同。**

&nbsp;

## 说明/提示

#### 样例1

3个选手（两个来自学系1，一个来自学系2）必须被选中，即与瓦法来自同一个学系的选手会被选中，所以一定有一个队员与他来自同一个学系。

#### 样例2

选手不足

#### 样例3

篮球队选中瓦法的情况一共有 3 种，其中 2 种中有与瓦法来自同一个学系的队员。

&nbsp;

$ 1 \leqslant n \leqslant 100 $

$ 1 \leqslant m \leqslant 1000 $

$ 1 \leqslant h \leqslant m $

$ 1 \leqslant s_i \leqslant 100$

## 样例 #1

### 输入

```
3 2 1
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2 1
1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 2 1
2 2
```

### 输出

```
0.666667
```

# 题解

## 作者：是个汉子 (赞：3)

### 题意

 yft所在的学校有 $m$ 个社团，他所在的社团编号是 $h$ 。现在yft受wjx命令需要从这 $m$ 个社团中随机挑出 $n$ 个人（$n$ 个人包括他自己），请问挑出的人存在和yft同社团的概率是多大。

### Solution

我们先考虑如果正着去选择可能的情况，$\cdots$ ，发现是很麻烦的，所以我们要**正难则反**。

统计不可能的情况，最后用 $1$ 减去即可。

设 $sum$ 为总人数，那么从 $sum-1$ 选 $n-1$ 个人是总情况数，从 $sum-a[h]$ 选 $n-1$ 个人是不可能的情况。 

则 $ans=1-\dfrac{C_{sum-a[h]}^{n-1}}{C_{sum-1}^{n-1}}$ ，因为两个组合数的分母部分相同，可以继续化简： $ans=1-\dfrac{(sum-a[h])*(sum-a[h]-1)\cdots (sum-a[h]-n-1)}{(sum-1)*(sum-2)\cdots (sum-n-2)}$ 

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=10010;
int n,m,h,a[N],sum;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
    scanf("%d%d%d",&n,&m,&h);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]),sum+=a[i];
    if(sum<n){
        puts("-1");
        return 0;
    }
    if(sum-a[h]<(n-1)){
        puts("1");
        return 0;
    }
    double ans=1.0;
    double x=sum-a[h],y=sum-1;
    for(int i=1;i<=n-1;i++){
        ans*=x/y;
        x--;y--;
    }
    printf("%.10f\n",1.0-ans);
    return 0;
}
```



---

## 作者：WCG2025 (赞：2)

这道题是一道排列组合的题，有点类似高中的盒子取球问题，关键就是在于理解题意
题意：从m个盒子中取n个球，在取了h盒中的一个球的条件下，求h盒还取了别的球的概率

可以这样求得
sum表示m个盒子中总共有多少个球
从sum-1中取n-1个球的情况数是总情况数
减去从sum-m[h]取n-1个球的情况数
即是要求的情况数
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
       if(ch=='-') f=-1;
       ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
       x=x*10+ch-'0';
       ch=getchar();
    }
    return x*f;
}
int m[1111];
int n,mm,h;
int main()
{ 
    n=read();
    mm=read();
    h=read();
    int sum=0;
    for(int i=1;i<=mm;i++)
    {
        m[i]=read();
        sum+=m[i];
    }
    if(sum<n)
        cout<<-1<<endl;
    else
    {
        double ans=1;
        for(int i=0;i<n-1;i++)
            ans*=(sum-m[h]-n+2+i)*1.0/(sum-n+1+i);
        ans=1-ans;
        cout<<ans<<endl;
    }
}

```
码风丑陋，若引起不适
sorry for trouble caused

---

## 作者：XL4453 (赞：2)

### 解题思路：

简单组合问题，式子和其他人推的不太一样。

正难则反，其实就是一个“抛硬币至少有一次正面”的类似问题。

---

将所有的人划分成几个集合，必选的那个人，和那个人一个系的其他学生，设为 $a$，不和那个人一个系的学生，设为 $b$。

把必选的那一个人抛开讨论，也就是要求从 $a+b$ 个人中选择 $k-1$ 个人使得不存在 $a$ 中的人。

考虑求出全是 $b$ 中人的概率，然互用 $1$ 去减就得到了答案，也就是 $1-\dfrac{\dbinom{b}{k-1}}{\dbinom{a+b}{k-1}}$。由于没有取模，直接求然后做除法会炸。

所以化下来，得到：$1-\dfrac{\dfrac{b!}{(k-1)!(b-k+1)!}}{\dfrac{(a+b)!}{(k-1)!(a+b-k+1)!}}$。

然后约分，得到：$1-\dfrac{\dfrac{b!}{(b-k+1)!}}{\dfrac{(a+b)!}{(a+b-k+1)!}}$。

换下位置，写漂亮一点：$1-\dfrac{\prod_{i_1=1}^{b}i_1\ \prod_{i_2=1}^{a+b-k+1}i_2}{\prod_{i_3=1}^{a+b}i_3\ \prod_{i_4=1}^{b-k+1}i_4}$。

然后再化：$1-\dfrac{\prod_{i_2=b-k+2}^{a+b-k+1}i_2}{\prod_{i_1=b+1}^{a+b}i_1}$。

这个式子求起来就很方便啦。

---

~~好在这题不卡精度，不然后不知道要调多久。~~

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,k,h,a,b,x;
double ans;
int main(){
	scanf("%d%d%d",&k,&n,&h);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(i==h)a=x;
		else b+=x;
	}
	if(k>a+b){
		printf("-1\n");
		return 0;
	}
	ans=1;a--;
	for(int i=1;i<=a;i++)
	ans=ans*(b-k+1+i)/(b+i);
	ans=1-ans;
	printf("%.8lf",ans);
	return 0;
}
```


---

## 作者：qwq___qaq (赞：1)

设总人数为 $sum$，那么当 $sum<n$ 时，人数不够，输出 $-1$。

考虑容斥：用 $1$ 减去不包含 $h$ 的概率。

总情况，也就是其他人中选择 $n-1$ 个，那么方案数就是 $C_{sum-1}^{n-1}$。不包含 $h$ 的情况，那就是从除了 $h$ 之外的选择 $n-1$ 个，方案数是 $C_{sum-s_h}^{n-1}$。

那么答案就是 $1-\dfrac{C_{sum-s_h}^{n-1}}{C_{sum-1}^{n-1}}$。

但是要注意一个实现细节。

- 直接算阶乘会爆，得到 `inf`，可以采用 $C_n^m=C_{n-1}^{m-1}\times\dfrac{n}{m}$ 这个公式。

- 这样仍然会爆，需要把 `double` 改成 `long double`。

---

## 作者：cirnovsky (赞：1)

## 题意简述

从第一篇题解贺过来的。

从 $m$ 个盒子中取 $n$ 个球，在取了 $h$ 盒中的一个球的条件下，求 $h$ 盒还取了别的球的概率。

## 题解

一个不太一样的式子。。。

令

$$
S=\sum_{i=1}^{m}s_{i}
$$
所有情况数：
$$
{S-1\choose n-1}
$$
不可能的情况数：
$$
{S-m_{h}\choose n-1}
$$
答案：
$$
1-\frac{{S-m_{h}\choose n-1}}{{S-1\choose n-1}}
$$
但是这题没模数，所以我们只能继续化简（摊手）。
$$
\begin{aligned}
\mathrm{ANS}
&=1-\frac{{S-m_{h}\choose n-1}}{{S-1\choose n-1}} \\
&=1-\frac{\frac{(S-m_{h})!}{(n-1)!(S-m_{h}-n+1)!}}{\frac{(S-1)!}{(n-1)!(S-n)!}} \\
&=1-\frac{\frac{(S-m_{h})!}{(n-1)!(S-m_{h}-n+1)!}\times(n-1)!(S-n)!}{(S-1)!} \\
&=1-\frac{\frac{(S-m_{h})!}{(S-m_{h}-n+1)!}\times(S-n)!}{(S-1)!} \\
&=1-\frac{\frac{(S-m_{h})!}{(S-n+2-m_{h}-1)!}\times(S-n)!}{(S-1)!} \\
&=1-\frac{\frac{(S-n)!}{(S-n-(m_{h}-1))!}\times(S-m_{h})!}{(S-1)!} \\
&=1-\frac{(\prod_{i=S-n-m_{h}+2}^{S-n}i)\times(S-1-(m_{h}-1))!}{(S-1)!} \\
&=1-\frac{(\prod_{i=S-n-m_{h}+2}^{S-n}i)}{\prod_{i=S-m_{h}+1}^{S-1}i} \\
\end{aligned}
$$

特别牛逼的是，我验证样例的时候算错了一直觉得这个式子是错的，结果。。。

另一个特别牛逼的是，我认为这个式子会爆 `double`，于是又化简了半天，结果直接过了。。。

```cpp
#include <cstdio>

const int MAXN = 1e3 + 5;

int N, M, H, S;
int nums[MAXN];

int main( ){
	scanf( "%d%d%d", &N, &M, &H );
	for( int i = 1; i <= M; ++ i ){ scanf( "%d", &nums[i] ); S += nums[i]; }
	if( S < N ){ puts( "-1" ); return 0; }
	double Ans = 1;
	for( int i = S - N - nums[H] + 2; i <= S - N; ++ i )	Ans *= i;
	for( int i = S - nums[H] + 1; i <= S - 1; ++ i )	Ans /= i;
	printf( "%.10lf\n", 1 - Ans );
	return 0;
}
```

---

## 作者：TemplateClass (赞：0)

记 $t = \sum _ {i = 1} ^ {m} s _ i$，然后先把 $n > t$ 的情况判了，此时没有足够的球员，输出 `-1`。

正难则反。抛开必选的 Herr Wafa，那么就是我们要在的 $t$ 个人中选择 $n - 1$ 个人使得不存在学系 $h$ 中的人。换句话说，我们需要在 $t - s _ h$ 个人中选 $n - 1$ 个人，用它去除以不考虑学系限制（即在 $t - 1$ 个人中选 $n - 1$ 个人）的方案数，就得到了不存在学系 $h$ 中的人的概率，用 $1$ 去减即可。

所以答案即为：

$$
\begin{aligned}
1 - \dfrac{\dbinom{t - s _ h}{n - 1}}{\dbinom{t - 1}{n - 1}} &= 1 - \dfrac{\dfrac{(t - s _ h) !}{(n - 1)!(t - s _ h - (n - 1))!}}{\dfrac{(t - 1)!}{(n - 1)!(t - 1 - (n - 1))!}} \\[8mm] &= 1 - \dfrac{(t - s _ h)!(t - n)!}{(t - 1)!(t - s _ h - n + 1)!} \\[4mm] &= 1 - \dfrac{\left( \prod \limits _ {i = 1} ^ {t - s _ h} i \right)\left( \prod \limits _ {i = 1} ^ {t - n} i \right)}{\left( \prod \limits _ {i = 1} ^ {t - 1} i \right)\left( \prod \limits _ {i = 1} ^ {t - s _ h - n + 1} i \right)} \\[8mm] &= 1 - \dfrac{\left( \prod \limits _ {i = 1} ^ {t - s _ h} i \right)\left( \prod \limits _ {i = 1} ^ {t - s _ h - n + 1} i \right)\left( \prod \limits _ {i = t - s _ h - n + 2} ^ {t - n} i \right)}{\left( \prod \limits _ {i = 1} ^ {t - s _ h} i \right)\left( \prod \limits _ {i = t - s _ h + 1} ^ {t - 1} i \right)\left( \prod \limits _ {i = 1} ^ {t - s _ h - n + 1} i \right)} \\[8mm] &= 1 - \dfrac{\prod \limits _ {i = t - s _ h - n + 2} ^ {t - n} i}{\prod \limits _ {i = t - s _ h + 1} ^ {t - 1} i}
\end{aligned}
$$

直接计算即可，`double` 精度可直接过，时间复杂度 $O(s _ h)$。

---

## 作者：liuli688 (赞：0)

### 思路
如果要算所有可能的情况不太好算，所以我们可以先算出总方法数，再算出不可能的方法数，二者相除就可以了。

总方法数显然是从所有人中选 $(\texttt{总人数}- 1)$ 个人（不包括自己），那么公式是 $C _ {\texttt{总人数}-1} ^ {n - 1}$。

接下来再考虑不可能的方案。因为不能有和 Wafa 在同一个院系的人入选，所以要在剩下的院系中挑 $(\texttt{总人数}- 1)$ 个人。方案数 $C _ {\texttt{总人数}-s_h} ^ {n-1}$。

相除即可得到答案。
### 代码
```
#include <bits/stdc++.h>
using namespace std;

#define reg register

int n,m,h,sum = 0,s[1001];
double u,d,ans = 1;

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> h;
    --h;
    for(reg int i = 0;i < m;++i)
    {
        cin >> s[i];
        sum += s[i];//总人数
    }
    if(sum < n)//人不够
    {
        cout << -1;
        return 0;
    }
    if(sum - s[h] < n - 1)
    {
        cout << 1;
        return 0;
    }
    u = sum - s[h];
    d = sum - 1;
    for(reg int i = 0;i < m;++i)//计算
    {
        ans *= u / d;
        --u;--d;
    }
    cout << 1 - ans;
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑容斥。

用任意组成球队的方案数减去不含和瓦法同系的球队方案数再除总方案数。

设不含瓦法的总人数为 $cnt$，不含瓦法所在系的总人数为 $cnt1$，瓦法所在系中不含瓦法的人数为 $s$。

那么总方案数就是 $C^{n}_{cnt}$，不含瓦法同系的方案数为 $C^{n}_{cnt1}$（其中 $n$ 是题目中的 $n$ 减去 $1$，因为瓦法已经固定了）。

然后答案就是：
$$
\frac{C^{n}_{cnt}-C^{n}_{cnt1}}{C^{n}_{cnt}}\\
= 1-\frac{C^{n}_{cnt1}}{C^{n}_{cnt}}\\
= 1-(\frac{cnt1!}{n!(cnt1-n)!} \cdot \frac{n!(cnt-n)!}{cnt!})\\
= 1-(\frac{cnt1! \cdot (cnt-n)!}{cnt! \cdot (cnt1-n)!})
$$

将 $cnt = cnt1 + s$ 带入得：
$$
1-(\frac{cnt1! \cdot (n-cnt)!}{cnt! \cdot (n-cnt1)!})\\
=1-(\frac{cnt1! \cdot (cnt1 + s -n)!}{(cnt1+s)!\cdot(n-cnt1)!})\\
=1-(\frac{(cnt1-n+1)(cnt1-n+2)\dots(cnt1-n+s)}{(cnt1+1)(cnt1+2)\dots(cnt1+s)})
$$

然后直接算即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, h;
int cnt, cnt1;
long double S = 1;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> h;
	int cc;
	for (int i = 1; i <= m; ++i) {
		int s; cin >> s;
		if (i == h) {
			--s;
			cnt += s;
			cc = s;
		} else cnt1 += s, cnt += s;
	}

	--n;

	if (cnt < n) {
		puts("-1");
		return 0;
	}

	for (int i = 1; i <= cc; ++i) {
		S = S / (cnt1 + i);
		S = S * (cnt1 + i - n);
	}

	printf("%.10Lf", 1 - S);

	return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

简化题意。有 $m$ 组数，每一组有 $a_i$ 个。从 $m$ 组中选出 $n$ 个数,其中第 $h$ 组数至少选 $1$ 个，求再次选到第 $h$ 组的数的概率。

先考虑正着做，发现要考虑 $a_h$ 种情况，即枚举从第 $h$ 组中选出数的个数，很麻烦。

考虑反着做。我们发现，可以求出**没有数再次在第 $h$ 组的情况**，然后求出总的情况，得出**没有数再次在第 $h$ 组的概率**，最终用 $1$ 减去即可。

设 $sum = \sum a_i$，则没有数在再次第 $h$ 组的情况总数为 $C_{sum - a_h}^{n - 1}$，即从除了第 $h$ 组的所有组中选出 $n - 1$ 数。没有数再次在第 $h$ 组的概率就为：

$${\large \frac{C_{sum - a_h}^{n - 1}}{C_{sum - 1}^{n - 1}}} = \frac{(sum - a_h) \times (sum - a_h - 1) \times \cdots \times (sum - a_h - n + 2)}{(sum - 1) \times (sum - 2) \times \cdots \times (sum - n + 1)} $$

然后把每一位拆开计算，得出：

$${\large \frac{sum - a_h}{sum - 1} \times \frac{sum - a_h - 1}{sum - 2} \times \cdots \times \frac{sum - a_h - n + 2}{sum - n + 1}}$$

最终答案即为：

$$1 - {\large \frac{sum - a_h}{sum - 1} \times \frac{sum - a_h - 1}{sum - 2} \times \cdots \times \frac{sum - a_h - n + 2}{sum - n + 1}}$$

---

