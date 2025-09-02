# Walking Between Houses

## 题目描述

在一条路上，$n$ 个房子被排成一排，从从左到右编号为 $1\sim n$。一开始，你站在 $1$ 号房子前。

你需要移动到其他的房子 $k$ 次。每一次移动，你不能原地不动（即移动后与移动前，你必须在不同的房子前面）。如果你从 $x$ 房子移动到 $y$ 房子，那么你走过的距离就是 $\left\vert x-y \right\vert$，这里 $\left\vert a \right\vert$ 表示 $a$ 的绝对值。当然，你可以访问同一个房子多次。（只要不连续就行了）

你的目标是一共走 $s$ 个单位长度。

如果是不可能的，输出 $\texttt{NO}$，否则输出 $\texttt{YES}$，并输出任意一种移动方案，记住你只能走恰好 $k$ 次。

## 样例 #1

### 输入

```
10 2 15
```

### 输出

```
YES
10 4 
```

## 样例 #2

### 输入

```
10 9 45
```

### 输出

```
YES
10 1 10 1 2 1 2 1 6 
```

## 样例 #3

### 输入

```
10 9 81
```

### 输出

```
YES
10 1 10 1 10 1 10 1 10 
```

## 样例 #4

### 输入

```
10 9 82
```

### 输出

```
NO
```

# 题解

## 作者：1517460958dyc (赞：6)

和楼上**大佬**思路不大一样但有些类似：我用的是分步方法。

**特判**当然是一样的：每次能走1~（n-1）格，k次能走k~k(n-1)格，s必须在此范围内。

**显然**每步走（s/k）格最接近目标，还剩下（s%k）格。将（s%k）格分入前（s%k）步中，每步一格，保证不超过n（因为s/k<=n-1且=时s%k==0）,是合法方案。

>### **以下是代码:(蒟蒻认为，此题难度绝没有达到紫题！)**
```cpp
#include<iostream>
using namespace std;
long long n,k,s;
int main()
{
    cin>>n>>k>>s;
    if (k*(n-1)<s||k>s)
    {
        cout<<"NO";
        return 0;
    }//特判
    cout<<"YES\n";
    long long t=1;
    for (int i=1;i<=s%k;i++)
    {
        if (i&1)
            t=s/k+2;
        else
            t=1;
        cout<<t<<' ';
    }//处理余数部分
    for (int i=s%k+1;i<=k;i++)
    {
        if (t<=(s/k))
            t+=s/k;
        else
            t-=s/k;
        cout<<t<<' ';
    }//不带余数部分
    return 0;
}
```
**蒟蒻**在此预祝各位**大佬**下次**AK**Div.3, **叉人必中**（别叉我233）！

---

## 作者：zhangqiuyanAFOon2024 (赞：2)

我们先读题，一眼看去，是道构造。

我们知道 $\lfloor\frac{a}{b}\rfloor\times b+a\bmod b=a$。

所以，跟据这个来构造就可以了。

我是这样想的：前 $a\bmod b$ 个数走 $\lfloor\frac{a}{b}\rfloor+1$ 格，然后其他 $b-a\bmod b$ 次都走$\lfloor\frac{a}{b}\rfloor$ 格。

证明：

$a\bmod b\times(\lfloor\frac{a}{b}\rfloor+1)+(b-a\bmod b)\times(\lfloor\frac{a}{b}\rfloor)$

$=\lfloor\frac{a}{b}\rfloor\times b+a\bmod b$

$=a$。

结论成立。

注意

1.要开 `long long`。

2.住意越界。

3.特判 NO。

4.变量名改过，注意分析。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,k,s;
	cin>>n>>k>>s;
	if(k*(n-1)<s||k>s){
		cout<<"NO";
		return 0;
	}//特判
	cout<<"YES"<<endl;
	int cnt=1;
	for(int i=1;i<=s%k;i++){
	   if(i%2==0) cout<<1<<' ',cnt=1;
		else cout<<s/k+2<<' ',cnt=s/k+2;
	}//第一个，s/k+2-1=s/k+1
	for(int i=s%k+1;i<=k;i++){
		if(cnt<=s/k) cout<<cnt+s/k<<' ',cnt+=s/k;//变成负数可不好
		else cout<<cnt-s/k<<' ',cnt-=s/k;
	}//第二个
	return 0;
}
```
完结撒花！

---

## 作者：EightSixSun (赞：2)

首先判断两种不能实现的情况
```
1.剩余(就是从第一步开始，但是这样说概括比较广泛)的平均每步要走的距离>(n-1)
2.s<k，即平均每步要走的距离不到1
```
特判这两种情况输出”NO” 
否则就输出”YES” 
然后就是怎么走的问题了 
我们肯定是希望当前位置可以到达的距离远一些，不希望当前位置居中 

那我们就先判断在左半区间还是右半区间，优先向靠边的方向走

但是如果走不了就向另一个方向走

一直循环走到最后即可

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

#define For(i,l,r) for(int i=l;i<=r;++i)

using namespace std;
int n,k;
long long s;
int main()
{
    long long temp;
    cin>>n>>k>>s;
    temp=ceil((double)(s/(double)k));
    if(temp>n-1||s<k)
    {
        cout<<"NO";
        return 0;
    }
    cout<<"YES\n";
    int now=1;
    For(i,1,k)
    {
        temp=ceil((double)(s/(double)(k-i+1)));
        s-=temp;
        if(now<=n/2&&now-temp>0)
        {
            now-=temp;
            cout<<now<<" ";
            continue;
        }
        if(now+temp<=n)
        {
            now+=temp;
            cout<<now<<" ";
            continue;
        }
        now-=temp;
        cout<<now<<" ";
    }
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：1)

# 题解：CF1015D Walking Between Houses
## 算法
模拟，分类讨论
## 分析
首先，设每步走的距离为 $t_i$，我们发现 $t_i$ 应是满足 $1\le t_i\le n-1$ 的。那么就很容易推出 `NO` 的情况：
- 当 $s<k$ 时，由于每一步都要至少走一个单位，所以 $k$ 次步数肯定用不完，而题目要求恰好 $k$ 次；
- 当 $\frac{s}{k}>n-1$ 时，此时我们把每一步都撑到了最大的距离也就是 $n-1$ 个单位，但仍不满足要求，所以判负。

判完 `NO` 后，余下的就都是 `YES` 的情况，考虑怎么构造方案。

- 如果 $k\mid s$，容易想到一种构造方案为 $\frac{s}{k},1,\frac{s}{k}，…,1,\frac{s}{k}(,1)$。

- 如果 $k\nmid s$，说明 $s\div k$ 存在余数，那我们以上一种情况的方式处理后将余数加上即可。为了方便处理，我采用了上取整再将多走的距离减去的方法。这时多走的距离就是 $\left\lceil\dfrac{s}{k}\right\rceil\times k-s$。注意，在中间的某处减去一个单位的距离相当于少走了两个单位的距离（如 $1,3,1$ 变为 $1,2,1$），那么在余数为奇数时，将中间的减完后会剩 $1$，我们需要在结尾处理，此时需分类讨论。
	1.	当 $k$ 为偶数时，原本 $k$ 回到开头 $1$，但因为我们处理剩下多走了 $1$ 个单位的距离，所以我们少走一个应回到 $2$。
   2.	当 $k$ 为奇数时，原本 $k$ 会走到后面的 $\frac{s}{k}$ 处，但因为我们多走了 $1$ 个单位，所以我们将结尾走到的位置减 $1$。
   
最终输出答案即可，注意要开 `long long`，不然会 `Wrong answer on test 8`。


## 示例代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
namespace Ryan
{
    const int N=2e5+5;
    vector<int> v;
    int n,k,s;
    signed work()
    {
        cin>>n>>k>>s;
        if(k>s||s*1.0/k>(n-1))
        {
            cout<<"NO"<<endl;
            return 0;
        }
        for(int i=1;i<=k;i++)
        {
            if(i&1)
                v.push_back(ceil(s*1.0/k)+1);
            else 
                v.push_back(1);
        }
        if(s%k)
        {
            int ss=ceil(s*1.0/k)*k-s;
            // cout<<ss<<"**\n";
            for(int i=1;i<=k&&ss-2>=0;i+=2)
            {
                ss-=2;
                v[i-1]--;
            }
            if(ss)
            {
                if(k&1)
                    v[k-1]-=1;
                else 
                    v[k-1]+=1;
            }
        }
        cout<<"YES"<<endl;
        for(auto it:v)
            cout<<it<<" ";
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Ryan::work();
}
```

---

## 作者：sto__Liyhzh__orz (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF1015D)

### [博客](https://www.luogu.com.cn/blog/Lyhz0821/solution-cf1015d)

首先我们要判断 `NO` 的情况

+ 若每一步都走得尽可能长了，依然无法满足 $s$，则输出 `NO`，即 $(n-1) \times k < s$ 的情况。

+ 若每一步都走得尽可能短了，依然比 $s$ 大，也输出 `NO`，即 $k > s$ 的情况。

剩下的就是 `YES` 的情况了。

那怎么算出每次走多少呢？

令 $ sum \gets s \bmod k$。

先平均一点，每步先走 $\lfloor s / k \rfloor$，当然，还会剩下 $sum$ 的路程，可以将 $sum$ 依次分配到 $sum$ 步里。

我是用的数组存放每一次的步数的。

注意：$a_0$ 应为 $1$，比如样例二，不赋值的话，第二行输出为 ```
5 10 5 10 5 10 5 10 5```。

但在第一步时从 $1$ 到 $5$，只行了 $4$ 个距离，共只有 $44$ 个距离。

正确输出应为 ```6 1 6 1 6 1 6 1 6```（这里卡了我 $10$ 分钟）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const int MAXN=200000+5; 
LL k,n; 
LL s,a[MAXN];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k>>s;
    n--;
    a[0]=1;
    if(n*k<s || k>s) return cout<<"NO"<<endl,0;
    cout<<"YES"<<endl;
    for(int i=1;i<=s%k;i++) a[i]=(i&1)?(s/k+2):1;
    for(int i=s%k+1;i<=k;i++)
    {
        a[i]=a[i-1]+(a[i-1]<=s/k?s/k:-s/k);
    }
    for(int i=1;i<=k;i++) cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}

```

---

## 作者：dbxxx (赞：1)

[可以在我的博客中查看本文，谢谢。](https://www.cnblogs.com/crab-in-the-northeast/p/cf1015d.html)

容易判断掉两种无解情况：$s < k$ 或 $s > (n - 1)k$。因为每一步的步长范围是 $1 \sim n - 1$。

剩下的情况一定有解吗？不太知道。试着构造一下。

比较容易想到 $1 \to p \to 1 \to p \to 1 \cdots$ 跳 $k$ 次，其中 $p = \lfloor \dfrac{s}{k} \rfloor + 1$。这样会跳出 $s - s \bmod k$ 步，离 $s$ 步的目标比较接近。

那么剩下的 $s \bmod k$ 步怎么办？由于 $s \bmod k < k$，把 $s \bmod k $ 步中每一步分别放在前 $s \bmod k$ 个跳跃即可。

即：前 $s \bmod k$ 步的步长为 $p$，后 $s \bmod k$ 步的步长为 $p - 1$。

容易发现有两种情况：

- $1 \to p + 1 \to 1 \to \cdots \to p + 1 {\color{red} \to} 1 \to p \to 1 \to p \to \cdots$，对应 $s \bmod k$ 为偶数；
- $1 \to p +1 \to 1 \to \cdots \to 1 {\color{red} \to} p + 1 \to 2 \to p + 1 \to 2 \to p + 1 \to \cdots$，对应 $s \bmod k $ 为奇数。

上面的红色箭头代表最后一次步长为 $p$ 的跳跃，这次跳跃应该恰好是第 $s \bmod k $ 次跳跃。

那么接下来只需要证明这样不会跳出去即可。

- 当 $s < (n - 1)k$ 时，$p +1 \le n$，跳不出去；
- 当 $s = (n-1)k$ 时，虽然 $p +1 > n$，但是此时 $s \bmod k = 0$，因此一开始步长就是 $p - 1$ 了，实际的跳跃情况是 $1 \to p \to 1 \to p \to \cdots \to 1$。这里 $p = n$，因此跳不出去。

时间复杂度 $\mathcal{O}(k)$。~~全在输出上。~~

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-14 03:00:45 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-14 03:14:54
 */
#include <bits/stdc++.h>

#define int long long

inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

signed main() {
    int n = read(), k = read(), s = read();

    if (s < k || s > (n - 1) * k) {
        puts("NO");
        return 0;
    }

    puts("YES");
    int p = s / k + 1, q = s % k;

    if (q & 1) {
        for (int i = 1; i <= k; ++i, putchar(' ')) {
            if (i & 1)
                printf("%lld", p + 1);
            else if (i < q)
                putchar('1');
            else
                putchar('2');
        }
    } else {
        for (int i = 1; i <= k; ++i, putchar(' ')) {
            if (i & 1) {
                if (i < q)
                    printf("%lld", p + 1);
                else
                    printf("%lld", p);
            } else
                putchar('1');
        }
    }
    return 0;
}
```

---

## 作者：walk_alone (赞：1)

其实这题最纠结的地方在于：**什么时候留得青山在，不怕没柴烧，什么时候不要一步扯到蛋（一步跨太远）。**

首先是合法性判断，也是较为简单的一个部分，满足两个条件即可：$s>k$与$s<=(n-1)k$。前面一个判断容易被忽视掉，但是如果不考虑第五个点会错。不过只是个小错误，比较容易发现。

考虑到$s=k*(s/k)$，因此可以有以下两种安排方法：

第一，以k为主导，每步步长灵活机动。能跨大的尽量跨大的$(n-1)$，然后出一些小步子，最后一步一步的踱步。我一开始并没有意识到这个小步子的存在，以为就直接先$n-1$走，走到走不下去了就直接走1，最后剩多少一步走完，结果被

```cpp
10 9 45
```
 这个样例教训了……这样算最后一步要走7，到的位置是4，结果向前走不是向后走不是，崩掉。所以引入了这个小步子，介于$(n-1)$与$1$之间，用于填补剩的一步太少而一个最大步太多的情况。所以可以这样安排：先能走$(n-1)$就走，最后如果$(n-1)(i+1)>s$跳出这一循环，假设这一阶段总步数为sum，走了i步，开始一步一步踱步，直到$(s-sum)$%$(k-i)==0$，这个时候就可以全走小步子$(s-sum)/(k-i)$了。
 
 第二，以$s/k$为主导，每步尽量走这个长度，多余者拿最开始几步填坑。这个是第一篇题解的做法，先处理余数，每步都在$s/k$的基础上多走$1$格，先把$s-s*(s/k)$处理掉，剩下的步数直接在上个阶段的基础上步长$s/k$左右横跳。
 
 方法如果清楚了之后代码就是大模拟了，就不放我那丑陋的代码了。

---

## 作者：wmrqwq (赞：0)

duel 到的。

# 题目链接

[CF1015D Walking Between Houses (luogu)](https://www.luogu.com.cn/problem/CF1015D)

[CF1015D Walking Between Houses (codeforces)](http://codeforces.com/problemset/problem/1015/D)

# 解题思路

一道细节题。

思路很简单，肯定是一开始能走的越多越好，因此就有一种较好实现的方案，先每次走 $n - 1$ 格，但由于每次至少要走一格，因此如果不够走了就把能走的都走掉，之后全走 $1$ 步即可。

时间复杂度 $O(k)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
ll t;
ll n,m,k;
ll now,pd;
void solve()
{
	cin>>n>>m>>k;
	if(k<m || k>(n-1)*m)
	{
		cfn;
		return ;
	}
	cfy;
	now=1;
	while(m)
	{
		m--;
		if(pd==1)
		{
			if(now==1)
				cout<<++now<<' ';
			else
				cout<<--now<<' ';
			continue;
		}
		k-=n-1;
		if(k<m)
		{
			k+=n-1;
			ll sum=k-m;
			if(now==1)
				cout<<now+sum<<' ',now+=sum,pd=1;
			else
				cout<<now-sum<<' ',now-=sum,pd=1;
		}
		else
		{
			if(now==1)
				cout<<n<<' ',now=n;
			else
				cout<<1<<' ',now=1;
		}
	}
}
int main()
{
	IOS;
	t=1;
 //	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：Harrylzh (赞：0)

首先考虑极端情况，排除错误的数据。当让每一步走得**最小**时为 $1$ ，总步数为 $k$ ；当让每一步走得**最大**时为 $n-1$ ，总步数为 $k(n-1)$ 。所以 $s$ 的**最小值**为 $k$ ，**最大值**为 $k(n-1)$ ，如果 $s$ 超过了这个范围，就直接输出 ```NO``` 结束。

接下来考虑在范围内的情况，因为这些都可以通过在范围内改变每一步的长度得到，所以直接输出 ```YES``` 。然后考虑如何构造，设目前还没走的路程为 $x$ ，还剩的次数为 $y$ ，就走 $ \frac{x}{y}$ 步，一去一回地走，这样每一次走的都差不多。如果取 $ \lfloor\frac{x}{y}\rfloor$ ，那先走的其实是小于平均值的，走的步数会越来越大，可能会超出边界，所以取 $\lceil\frac{x}{y}\rceil$ 。

细节：
- 得出结果后要更新变量。
- 不开 long long 见祖宗。

代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
long long n,k,s;
long long now=1;//目前位置
int main()
{
    cin>>n>>k>>s;
    if(s>k*(n-1)||s<k)//判断超出范围的错误情况
    {
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    for(int i=k;i>=1;i--)//i表示还剩的次数
    {
        int v=ceil(1.0*s/i);//目前要走的步数
        if((k-i)%2==0) now+=v;
        else now-=v;//更新位置（一来一回）
        s-=v;//更新剩余路程
        cout<<now<<' ';
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 思路
因为要走满 $k$ 次，所以咱们就可以求出他能移动的最少距离和最多距离。

* $k$ 次（最小值）
* $(n-1)*m$ 次（最大值）

如果要走的步数不在这个区间中，就说明不可能走够，就输出"NO"。
然后，就要去确定每步走多远。于是，我们可以算一下平均数（向下取整），再算一下余数。余数代表有多少个数要比平均数（向下取整）多走一步。

设平均数（向下取整）为 $n$，那么第一步走到 $1+n$ ，第二步回到$1$，以此类推。

### 注意
要先枚举多走一步的，要不然可能会越界。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long//n*m会爆int
using namespace std;
int n,m,k,f=1;
signed main()
{
	cin>>n>>m>>k;
	if((n-1)*m<k||m>k)//不处于这个区间中
	{
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	int c=k/m,cy=k%m;
	for(int i=1;i<=cy;i++)//处理多走一步的
	{
		if(i%2==1)//往前走
		{
			cout<<c+2<<' ';
			f=c+2;
			continue;
		}
		//回到1
		cout<<1<<' ';
		f=1;
	}
	for(int i=cy+1;i<=m;i++)//不多走一步的
	{
		if(i%2==1)//往前走
		{
			cout<<f+c<<' ';
			f+=c;
			continue;
		}
		//回到1
		cout<<f-c<<' ';
		f-=c;
	}
	return 0;
}
```


---

