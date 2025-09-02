# Restore Modulo

## 题目描述

For the first place at the competition, Alex won many arrays of integers and was assured that these arrays are very expensive. After the award ceremony Alex decided to sell them. There is a rule in arrays pawnshop: you can sell array only if it can be compressed to a generator.

This generator takes four non-negative numbers $ n $ , $ m $ , $ c $ , $ s $ . $ n $ and $ m $ must be positive, $ s $ non-negative and for $ c $ it must be true that $ 0 \leq c < m $ . The array $ a $ of length $ n $ is created according to the following rules:

- $ a_1 = s \bmod m $ , here $ x \bmod y $ denotes remainder of the division of $ x $ by $ y $ ;
- $ a_i = (a_{i-1} + c) \bmod m $ for all $ i $ such that $ 1 < i \le n $ .

For example, if $ n = 5 $ , $ m = 7 $ , $ c = 4 $ , and $ s = 10 $ , then $ a = [3, 0, 4, 1, 5] $ .

Price of such an array is the value of $ m $ in this generator.

Alex has a question: how much money he can get for each of the arrays. Please, help him to understand for every array whether there exist four numbers $ n $ , $ m $ , $ c $ , $ s $ that generate this array. If yes, then maximize $ m $ .

## 样例 #1

### 输入

```
6
6
1 9 17 6 14 3
3
4 2 2
3
7 3 4
3
2 2 4
5
0 1000000000 0 1000000000 0
2
1 1```

### 输出

```
19 8
-1
-1
-1
2000000000 1000000000
0```

# 题解

## 作者：Priori_Incantatem (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1484B)  
[在我的Blog查看](https://blog.csdn.net/Brian_Pan_/article/details/115080672)

### 题目大意
给出一个序列 $a$，问是否能找到四个数 $n,m,s,c$，满足以下条件
1. $a$ 的长度为 $n$
2. $a_1=s \mod m$
3. $a_i=(a_{i-1}+c) \mod m \space | \space (1 < i \le n)$
4. $0 \le c < m$
5. $m$ 尽可能的大

如果不能找到这样的四个数，输出 `-1`  
如果 $m$ 可以任意大，输出 `0`  
否则，输出最大可能的 $m$ 和其对应的 $c$，如果有多个可能的 $c$，输出任意一个

### 解题思路

一道较为简单的数论+模拟题，但似乎在赛时卡掉了很多人

首先，因为 $0 \le c <m$，我们可以把 $\mod m$ 的操作换成：如果 $\ge m$，就减去 $m$。

那么，对于 $(1 < i \le n)$，就有如下两种可能：
1. $a_i=a_{i-1}+c-m$
2. $a_i=a_{i-1}+c$

可以发现，如果 $a_{i-1}+c \ge m$，就一定有 $a_i<a_{i-1}$。因为 $c-m<0$

现在，我们按顺序判断如下几种情况
1. 如果 $a_i \le a_{i+1} \space | \space 1 \le i <n$，且所有 $a_{i+1}-a_i$ 都相等，那么输出 $0$，因为生成序列式不需要取模
2. 当满足 $a_i > a_{i+1} \space | \space 1 \le i <n$，如果所有 $a_{i+1}-a_i$ 都相等，输出 $0$，否则输出 $-1$
3. 现在，已经满足了既有 $a_i> a_{i+1}$，也有 $a_i \le a_{i+1}$。那么，我们可以根据 $a_i \le a_{i+1}$ 的地方来求出 $c$。如果不能求出一个统一的 $c$，输出 $-1$。
4. 在求出了统一的 $c$ 之后，对于每一个 $a_i > a_{i+1}$ 的地方，可以求出 $m=a_i+c-a_{i+1}$。如果求出的 $m$ 是统一的且 $m>c$，则输出 $m$ 和 $c$，否则输出 $-1$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
const int Maxn=1e5+10;
int n,m,val;
int a[Maxn];
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
bool check()
{
    if(n==1)return 1;
    bool flag=1;
    for(int i=1;i<n;++i)
    if(a[i]>a[i+1] || a[i]+m!=a[i+1])
    {flag=0;break;}
    if(flag)return 1;
    flag=1;
    for(int i=1;i<n;++i)
    if(a[i]<=a[i+1]){flag=0;break;}
    if(flag)
    {
        int tmp=a[1]-a[2];
        for(int i=2;i<n;++i)
        if(a[i]-a[i+1]!=tmp){flag=0;break;}
        if(flag)return 1;
    }
    return 0;
}
int calc()
{
    int tmp;
    for(int i=1;i<n;++i)
    {
        if(a[i]<=a[i+1] && a[i]+m!=a[i+1])
        return 0;
        if(a[i]<=a[i+1])continue;
        if((a[i]+m)-a[i+1]<=val)return 0;
        tmp=(a[i]+m)-a[i+1];
    }
    for(int i=1;i<n;++i)
    {
        if(a[i]<=a[i+1])continue;
        if(a[i]+m-a[i+1]!=tmp)return 0;
    }
    return tmp;
}
int main()
{
    // freopen("in.txt","r",stdin);
    int T=read();
    while(T--)
    {
        n=read();
        val=-1;
        for(int i=1;i<=n;++i)
        a[i]=read(),val=max(val,a[i]);
        for(int i=1;i<n;++i)
        if(a[i]<=a[i+1])m=a[i+1]-a[i];
        if(check()){puts("0");continue;}
        int tmp=calc();
        if(!tmp){puts("-1");continue;}
        printf("%d %d\n",tmp,m);
    }
    return 0;
}
```

---

## 作者：feicheng (赞：2)

## [$\text{Description}$](https://www.luogu.com.cn/problem/CF1484B)

给定长度为 $n$ 的序列 $a$，求是否存在最大的 $m$ 使得 $a$ 在模意义下是等差数列。

## $\text{Solution}$

首先我们要知道 $a_i$ 只有可能由以下两个式子推得：

$$ a_i=a_{i-1}+c\quad(1)$$
$$a_i=a_{i-1}+c-m\quad(2) $$

若由 $(1)$ 转移来，则说明 $a_i \ge a_{i-1}$ ，反之则有 $a_i < a_{i-1}$。

**结论：构造差分序列 $b$，$b_i=a_i-a_{i-1}$ 若有解，则 $b$ 中最多只有两个不相同的数字**

证明：

考虑分类讨论，若由上述 $(1)$ 转移来。则 $b_i = c$，反之 $b_i=c-m$。

特殊地：如果 $b$ 是常数列，则 $m$ 可取任何值。

如果 $\forall i\in[1,n],\exists b_i < 0$ 则无解。

排除上述情况之后就可以来计算 $m,c$ 的值了：

记 $b$ 中不同的两项数字为 $p,q$ ，则：

$m = |p|+|q|,c=\max(p,q)$ 

自己推下式子就可以证明了。

## $\text{Code}$

```cpp
/*If you are full of hope,you will be invincible*/
constexpr int N = 1e5 + 10;
int a[N],b[N],n,T;
std::unordered_map <int,bool> vis;
int num,ans,ans_;
inline void Solve() {
    vis.clear(),num=ans=ans_=0;        
    int mx = -1,tmp[3];
    read(n);
    memset(a,0,sizeof a),memset(b,0,sizeof b);
    for(int i = 1;i <= n;++i) read(a[i]),mx=max(a[i],mx);
    if(n == 1)  return ans = 0,void();
    for(int i = 2;i <= n;++i) b[i-1] = a[i] - a[i-1];//差分
    int num = 0;
    for(int i = 1;i <= n-1;++i) {
         if(!vis[b[i]]) tmp[++num] = b[i],vis[b[i]] = 1;
         if(num == 3) return ans = -1,void();//如果有三个不同的数
    }
    if(num == 1) return ans = 0,void();
    if(tmp[1] < 0 and tmp[2] < 0) return ans = -1,void();
    ans = abs(tmp[1]) + abs(tmp[2]),ans_ = max(tmp[1],tmp[2]);
    if(ans < mx) return ans = -1,void();
}
int main(int argc,const char **argv) {
    read(T);
    while(T--) {
        Solve();
        if(ans == -1 || ans == 0) print('\n',ans);
        else print(' ',ans,ans_),STD::putc('\n'); 
    }
    return STD::flush(),0;
}
```



---

## 作者：Acfboy (赞：1)

赛时 WA 了两次才过 qwq.

> 输入一个序列，请通过下面的方式构造它： $a_1 = s \mod m$ 且对于任意 $1 < i \le n$ 满足 $a_i = (a_{i-1} + c) \mod p$, 求最大的 $m$ 并输出一个合适的 $c$, 若没有答案输出 `-1`, $m$ 可以无限大输出 `0`.

首先考虑一些显而易见的 `-1` 的情况。

因为每次都对 $m$ 取模了，所以每次要么没有减去 $m$，要么加上 $c$ 减去 $m$ ，所以每组增加的相邻两个的增加量必须相同，减少的减少量也必须相同，不然就是 `-1`。

然后考虑显而易见的 `0` 的情况，只有增加的和只有减少的 $m$ 肯定可以无限大了，增加的则一直不取模即可，减少的设每次减少的是 $rec$, 则只要满足 $c-m = rec$ 就可以， $m$ 也可以无限大。

然后可以考虑正常情况了，显然，每次增加的就是 $c$ , 而这个条件也可以完美地限制住 $m$, 若 $a_i < a_{i-1}$，$m$ 只能是 $a_{i-1} + c - a_i$ 了，因为其中所有数都是小于 $m$ 的，所以这种情况只能是 $a_i = a_{i-1} + c - m$, 移项可得。

这样的做法真的对吗，增加也有可能取模过了啊！但这样子显然可以把 $m$ 调的更大而满足所有条件，不可能称为最大解。

记得还要判断 $m$ 是否有冲突和是否有数大于等于了求得的 $m$。

考场代码如下。

```cpp
#include <cstdio>
#define int long long
const int N = 100005;
int T, n, m, c, rec, a[N];
signed main() {
    scanf("%lld", &T);
    while(T--) {
        scanf("%lld", &n);
        c = -1, rec = -1, m = -1;
        for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        bool flag1 = false, flag2 = false, flag3 = false, flag4 = false;
        for(int i = 2; i <= n; i++) {
            if(c == -1 && a[i] >= a[i-1]) c = a[i] - a[i-1];
            else if(a[i] >= a[i-1] && a[i] - a[i-1] != c) {flag1 = true; break;}
            if(rec == -1 && a[i] < a[i-1])  rec = a[i-1] - a[i];
            else if(a[i] < a[i-1] && a[i-1] - a[i] != rec) flag2 = true;
        }
        if(flag1 || flag2) { puts("-1"); continue; }
        if(c == -1 && !flag2 || rec == -1 && !flag1) {puts("0"); continue; }
        for(int i = 2; i <= n; i++) 
            if(m == -1 && a[i] < a[i-1]) m = a[i-1] + c - a[i];
            else if(a[i] < a[i-1] && a[i-1] + c - a[i] != m) { flag3 = true; break;}
        if(flag3) { puts("-1"); continue; }
        for(int i = 1; i <= n; i++) 
            if(a[i] >= m) flag4 = true;
        if(flag4) puts("-1");
        else printf("%lld %lld\n", m, c);
    }
}
```

赛时的两次 WA 一次是因为没有判断数都小于 $m$ 的情况，一次是因为判断只上升出错了，认为 `rec == -1` 时只有 `c == 0` 才输出 `0`,且下降不均匀判 `-1` 需要只下降。 而实际上，只下降不均匀就可以判断 `-1`, 仅上升均匀无下降就可以判断 `0`。

---

## 作者：xuezhe (赞：1)

题目大意是给定 $a_1,a_2,\ldots,a_n$，求最大的 $m$ 满足给定序列是模 $m$ 意义下的等差数列。

首先可以发现若 $a_1,a_2,\ldots,a_n$ 本身就是等差数列，则 $m$ 可以无限大。

否则对序列差分，设 $b_i = a_{i+1} - a_i$，若 $b_i$ 中所有正数都等于一个数 $x$，所有负数都等于一个数 $y$，且 $x-y$ 大于 $a$ 中的所有数，则有解，$m$ 的最大值为 $x-y$，公差 $c$ 为 $x$，否则无解。

```cpp
const int N(100005);
int T,n,a[N],b[N];
void fakemain(){
    Read(T);
    while(T--){
        Read(n);
        for(int i=1;i<=n;++i)
            Read(a[i]);
        for(int i=1;i<n;++i)
            b[i]=a[i+1]-a[i];
        int flg=1;
        for(int i=2;i<n;++i)
            if(b[i]!=b[1])
                flg=0;
        if(flg){
            puts("0");
            continue;
        }
        int zh=-1,fu=1;
        for(int i=1;i<n;++i){
            if(b[i]>0){
                if(zh==-1)
                    zh=b[i];
                else if(zh!=b[i])
                    flg=1;
            }else if(b[i]<0){
                if(fu==1)
                    fu=b[i];
                else if(fu!=b[i])
                    flg=1;
            }else{
                flg=1;
            }
        }
        if(flg){
            puts("-1");
            continue;
        }
        for(int i=1;i<=n;++i)
            if(a[i]>=zh-fu)
                flg=1;
        if(flg){
            puts("-1");
            continue;
        }
        printf("%d %d\n",zh-fu,zh);
    }
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1484B)

------------

# 思路：
首先本题最重要的一个条件是 $0 \le c \lt m$，抓紧这个条件研究序列能发现：若 $a_{i+1}>a_i$，那么 $a_{i+1} - a_i = c$。因为 $a_i <m ( \forall i \in [1,n])$，因此 $a_i+c<2 \times m$，那么只要 $a_{i+1}<a_i$，我们就能求出 $m = a_i + c - a_{i+1}$，且这个 $m$ 一定是唯一的。

固定 $s,m$ 然后 $c$ 从 $m-1$ 开始递减，可以发现如果整个序列是递减的合法序列那么一定是等差递减，这时 $m$ 取 ```inf```，否则就不存在这样递减的序列。同理等差递增的序列。
若存在 $a_i =a_{i+1}$，那么 $c=0$，序列合法当且仅当序列的所有数都相等。

还有一个特判，$n$ 为 $1$ 或 $2$ 时 $m$ 取 ```inf```。另外在确定 $m,c$ 回代判断序列是否合法时注意还要判断 $a_i < m$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,a[N];
bool check(int m,int c){
    if(c>=m||m<=a[1])return 0;
    for(int i=1;i<n;i++){
        if(a[i]>=m||a[i+1]>=m){
			return 0;
		}
        if(a[i+1]>a[i]&&a[i+1]-a[i]!=c){
			return 0;
		}
        if(a[i+1]<a[i]&&(a[i]+c)%m!=a[i+1]){
			return 0;
		}
    }
    return 1;
}
bool SPJ(){
    for(int i=1;i<n;i++){
        if(a[i+1]==a[i]){
			return 1;
		}
    }
    return 0;
}
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
			cin>>a[i];
		}
        if(n==1||n==2){
            cout<<0<<endl;
            continue;
        }
        if(SPJ()){
            bool ok=1;
            for(int i=1;i<=n;i++){
                if(a[i]!=a[1]){
                    ok=0;
                    break;
                }
            }
            if(ok){
				cout<<0<<endl;
			}else{
				cout<<-1<<endl;
			}
            continue;
        }
        if(a[1]<a[2]){
            int i=2,c=a[2]-a[1],m;
            while(i<=n&&a[i]>a[i-1]){
				i++;
			}
            if(i==n+1){
                bool ok=1;
                int del=a[2]-a[1];
                for(int j=1;j<n;j++){
                    if(a[j+1]-a[j]!=del){
                        ok=0;
                        break;
                    }
                }
                if(ok){
					cout<<0<<endl;
				}else{
					cout<<-1<<endl;
				}
            }else{
                m=a[i-1]+c-a[i];
                if(check(m,c)){
					cout<<m<<" "<<c<<endl;
				}else{
					cout<<-1<<endl;
				}
            }
        }else if(a[1]>a[2]){
            int i=2,m,c;
            while(i<=n&&a[i]<a[i-1]){
				i++;
			}
            if(i==n+1){ 
                bool ok=1;
                int del=a[1]-a[2];
                for(int j=1;j<n;j++){
                    if(a[j]-a[j+1]!=del){
                        ok=0;
                        break;
                    }
                }
                if(ok){
					cout<<0<<endl;
				}else{
					cout<<-1<<endl;
				}
            }else{
                c=a[i]-a[i-1];
                m=a[i-2]+c-a[i-1];
                if(check(m,c)){
					cout<<m<<" "<<c<<endl;
				}else{
					cout<<-1<<endl;
				}
            }
        }
    }
    return 0;
}
```
完结撒花~

---

## 作者：Norsuman371 (赞：0)

# 思路

如这个数组是以恒定值递增或者递减则 $m$ 是可以无穷大的。

如这个数组有递增有递减，可以从递增的点找到 $c$，必须保证每一个递增的点都是恒定的 $c$，我们从递减的点找到 $m$，也必须每一个递减的点都是恒定的 $m$，然后还需要判断 $m$ 和这个数组最大值的比较，如数组最大值大于 $m$，那就输出 $-1$，如小于 $m$，那就输出 $m$ 和 $c$。

# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb push_back
#define me memset
#define PII pair<int,int>
#define PLL pair<ll,ll>
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
using namespace std;
int a[N];
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int maxx = 0;
        for (int i = 1; i <= n; i++) cin >> a[i], maxx = max(maxx, a[i]);
        if (n == 1 || n == 2) {
            cout << "0" << endl;
            continue;
        }
        bool flag1 = true;
        int v = a[2] - a[1];
        int c, m;
        for (int i = 1; i < n; i++) {
            if (a[i + 1] - a[i] != v) flag1 = false;
            if (a[i + 1] >= a[i]) c = a[i + 1] - a[i];
        }
        for (int i = 1; i < n; i++) {
            if (a[i] > a[i + 1]) m = a[i] + c - a[i + 1];
        }
        if (flag1) {
            cout << "0" << endl;
            continue;
        }
        bool flag2 = true;
        for (int i = 1; i < n; i++) {
            if (a[i] <= a[i + 1] && c != a[i + 1] - a[i]) flag2 = false;
            if (a[i] >= a[i + 1] && m != a[i] + c - a[i + 1]) flag2 = false;
        }
        if (!flag2) cout << "-1" << endl;
        else {
            if (m > c && m > maxx) cout << m << " " << c << endl;
            else cout << "-1" << endl;
        }
    }
    return 0;
}
```

# 记录

[洛谷老是UKE，懒得调了，直接转CF。](https://codeforces.com/problemset/submission/1484/264992321)

---

## 作者：Scean_Tong (赞：0)

## [$\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1484B)
## $\text{解题思路}$

首先我们要知道 $a_i$ 只有可能由以下两个式子推得：

$$ a_i=a_{i-1}+c$$
$$a_i=a_{i-1}+c-m $$

若由第一个式子转移来，则说明 $a_i \ge a_{i-1}$ ，反之则有 $a_i < a_{i-1}$。

**结论：构造差分序列 $b$，$b_i=a_i-a_{i-1}$ 如果有解，则 $b$ 中最多只有两个不相同的数字。**

可以发现，如果 $a_{i-1}+c \ge m$，就一定有 $a_i<a_{i-1}$。因为 $c-m<0$。

现在，我们按顺序判断如下几种情况：
1. 如果 $a_i \le a_{i+1} \space | \space 1 \le i <n$，且所有 $a_{i+1}-a_i$ 都相等，那么输出 $0$，因为生成序列式不需要取模。
2. 当满足 $a_i > a_{i+1} \space | \space 1 \le i <n$，如果所有 $a_{i+1}-a_i$ 都相等，输出 $0$，否则输出 $-1$。
3. 现在，已经满足了既有 $a_i> a_{i+1}$，也有 $a_i \le a_{i+1}$。那么，我们可以根据 $a_i \le a_{i+1}$ 的地方来求出 $c$。如果不能求出一个统一的 $c$，输出 $-1$。
4. 在求出了统一的 $c$ 之后，对于每一个 $a_i > a_{i+1}$ 的地方，可以求出 $m=a_i+c-a_{i+1}$。如果求出的 $m$ 是统一的且 $m>c$，则输出 $m$ 和 $c$，否则输出 $-1$。


## $\text{AC Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int a[N],b[N],n,T;
unordered_map <int,bool> q;
int num,ans,ans2;
void check() {
    q.clear();
	num=ans=ans2=0;        
    int mx = -1;
	int snow[3];
    cin>>n;
    memset(a,0,sizeof a);
	memset(b,0,sizeof b);
    for(int i = 1;i <= n;++i) {
		cin>>a[i];
		mx=max(a[i],mx);
	}
    if(n == 1)  {
		return ans = 0,void();
	}
    for(int i = 2;i <= n;++i) 
		b[i-1] = a[i] - a[i-1];
    int num = 0;
    for(int i = 1;i <= n-1;++i) {
         if(!q[b[i]]) snow[++num] = b[i],q[b[i]] = 1;
         if(num == 3) return ans = -1,void();
    }
    if(num == 1) return ans = 0,void();
    if(snow[1] < 0 and snow[2] < 0) return ans = -1,void();
    ans = abs(snow[1]) + abs(snow[2]),ans2 = max(snow[1],snow[2]);
    if(ans < mx) return ans = -1,void();
}
signed main() {
    cin>>T;
    while(T--) {
        check();
        if(ans == -1 || ans == 0) printf("%lld",ans);
        else printf("%lld %lld",ans,ans2);
		printf("\n");
    }
    return 0;
    
}
```



---

## 作者：ILQHDXAYG (赞：0)

## 题意：

给出一个 $n$ 和一个序列 $a$，求出最大的 $m$ 和对应的 $c$，使得 $a$ 的原数列为等差数列，公差为 $c$，给出的 $a$ 为模 $m$ 之后的序列，$c<m$；

$m$ 无解输出 $-1$，可以无穷大输出 $0$，有值有输出 $m$，$c$；

## 思路：

若 $a[i+1]>a[i]$ 则 $a[i+1]-a[i]=c$；
$a[i+1]<a[i]$。则 $a[i]-a[i+1]=m-c$；
可以推推看，$c<m$ 这个条件非常重要；

得到这两个结论后，遍历 $a$ 数组即可；

## Code：
```
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
#include <queue>
#include <utility>
#include <stack>
#include <map>
#include <vector>
#include <set>
#include <iomanip>
#define hz020 return
#define mes memset
#define mec memcpy

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int>pii;

const int N = 100010;
const int null = 0x3f3f3f3f;
const ll mod = 1000000007;

int T,n;
ll a[N];
ll b[N];
map<ll,int> mp;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

void solve()
{
	scanf("%d",&n);
		
	ll mmax = -1;
	for(int i = 1;i <= n;i ++) scanf("%lld",&a[i]),mmax = max(mmax,a[i]);
	
	ll c = -1,di = -1;
	for(int i = 1;i < n;i ++)
	{
		ll diff = a[i + 1] - a[i];
		if(diff > 0)
		{
			if(c == -1) c = diff;
			else
			{
				if(c != diff)
				{
					printf("-1\n");
					return ;
				}
			}
		}
		else
		{
			if(di == -1) di = -diff;
			else
			{
				if(di != -diff)
				{
					printf("-1\n");
					return ;
				}
			}
		}
	}
	
//	cout << c << " " << di << endl; 
	if(c == -1 || di == -1)
	{
		puts("0");
		return ;
	}
	ll m = di + c;
	if(mmax >= m)
	{
		puts("-1");
		return ;
	}
	b[1] = a[1];
	for(int i = 2;i <= n;i ++)
	{
		b[i] = (b[i - 1] + c) % m;
		if(b[i] != a[i])
		{
			puts("-1");
			return ;
		}
	}
		
	printf("%lld %lld\n",m,c);
}

int main()
{
	scanf("%d",&T);
	while(T --)
	{
		solve();
	}
	hz020 0;
}  

```
[转自](https://blog.csdn.net/m0_52348473/article/details/117366038)

---

## 作者：江户川·萝卜 (赞：0)

首先若是原数列是一个等差数列，相当于没有对 $m$ 取模这一操作，也就是 $m$ 可以取大于数列最大值的任意整数，也即题目中说的任意大，输出 `0`。

这是一个特判。

---

然后因为 $c<m$ ，所以模 $m$ 运算可看做减去 $m$。

那么 $a_i (i>1)$ 一共有两种形式：

1. $a_i=a_{i-1}+c$
2. $a_i=a_{i-1}+c-m$

移项，得：

1. $a_i-a_{i-1}=c$
2. $a_{i-1}-a_i=m-c$

发现了吗？要是 $a_i\ge a_{i-1}$，它俩的差为定值 $c$；要是 $a_i<a_{i-1}$，它俩的差为定值 $m-c$。（此处的差默认为大的减小的）

然后因为 $m=(m-c)+c$，两个值相加即为 $m$。

根据这个性质可以进行判断该数列是否存在 $m,c$。

如果算出来的某一个差出现不同，那么意味着这个数列不存在 $m$ 和 $c$。

否则，如果 $c$ 没有出现（也就是数列是递减），那么 $c$ 可以变得无穷大，此时 $m$ 也会变得无穷大。输出 `0` 即可。

如果两个值都有且分别始终保持一致，还要再算一下 $m$ 值是否大于数列最大值。

### Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[100005];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,maxx=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),maxx=max(maxx,a[i]);
		bool fl=true;
		for(int i=2;i<=n&&fl;i++) fl=(a[i]==a[i-1]);
		if(fl){puts("0");continue;}
		int c=-1,mmc=-1;fl=true;//mmc表示m-c
		for(int i=2;i<=n&&fl;i++){
			if(a[i]>=a[i-1]){
				if(c==-1) c=a[i]-a[i-1];
				else if(c!=a[i]-a[i-1]) fl=false;
			}
			else{
				if(mmc==-1) mmc=a[i-1]-a[i];
				else if(mmc!=a[i-1]-a[i]) fl=false;
			}
		}
		if(!fl||(c!=-1&&mmc!=-1&&c+mmc<=maxx)){puts("-1");}
		else if(c==-1||mmc==-1) puts("0");
		else printf("%d %d\n",mmc+c,c);
	}
	return 0;
} 
```

---

