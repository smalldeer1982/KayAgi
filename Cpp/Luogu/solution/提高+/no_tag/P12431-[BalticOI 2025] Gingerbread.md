# [BalticOI 2025] Gingerbread

## 题目描述

托伦自中世纪以来就以传统姜饼闻名。年轻的尼古拉斯想在他最喜欢的商店购买一套装有姜饼饼干的 $n$ 个盒子。不过这家店有非常严格的规定：尼古拉斯最初会得到 $n$ 个已经装有饼干的盒子，其中第 $i$ 个盒子初始装有 $a_{i}$ 块饼干。然后，尼古拉斯可以订购一些额外的饼干。他需要向某些盒子中添加额外的饼干，使得所有盒子中饼干数量的最大公约数$\text{*}$等于 1。可以证明这总是可行的。

请帮助尼古拉斯计算出，为了使所有饼干数量的最大公约数等于 1，需要添加的最少饼干数量。

$\text{*}$ 多个数的最大公约数（GCD）是指能整除所有这些数的最大正整数。

## 说明/提示

样例解释：初始时 90、84 和 140 的最大公约数是 2，因此必须添加饼干。如果只添加 1 块饼干，可能得到 91、84、140（GCD 为 7），或 90、85、140（GCD 为 5），或 90、84、141（GCD 为 3），这些都不满足要求。添加 2 块饼干（分别加到第一个和第二个盒子）后，得到 91、85、140，其 GCD 为 1，因此答案是 2。注意，如果将两块饼干都加到第一个盒子，会得到 92、84、140（GCD 为 4），这仍然不符合要求。

### 评分

| 子任务 | 限制条件 | 分值 |
| :---: | :---: | :---: |
| 1 | $n=2$ | 17 |
| 2 | $n \leq 10$ | 34 |
| 3 | $n \leq 1000$ | 11 |
| 4 | 无额外限制。 | 38 |

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
90 84 140```

### 输出

```
2```

# 题解

## 作者：diqiuyi (赞：2)

先把 $ans=0$ 判了。

先给 $a$ 排个序，然后考虑 $\gcd$ 的性质，把 $a$ 替换成它的差分。这时候的操作相当于 $a_i\gets a_i+1,a_{i+1}\gets a_{i+1}-1$。这时候 $\sum a_i$ 是 $O(V)$ 的。

有这样的结论：我们只要找到两个非空的无交的子序列且它们的和相同，那么 $ans=1$。证明就是找到这两个子序列中最靠后的那个，利用操作把它 $+1$，此时的 $\gcd$ 已经是 $1$ 了。

由抽屉原理可知，当 $2^n>V$ 时，$ans=1$。

所以我们只要考虑 $n\le 23$ 的情况，这时候直接从小到大枚举答案然后爆搜即可，复杂度不是很清楚，反正跑得很快，也完全卡不满。（其实由于上面的分析，$n>23$ 时也可以直接爆搜，不过无所谓了。并且实测这个 $n$ 的上界看起来是 $\omega(n)$ 级别的）
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int p[1000005],n,g;
void dfs(int x,int y,int now,int g){
	if(x==n){
		if(__gcd(g,p[x]+y-now)==1) cout<<y<<'\n',exit(0);
		return ;
	}
	for(int i=0;i<=y-now;i++)
		dfs(x+1,y,now+i,__gcd(g,p[x]+i));
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i],g=__gcd(g,p[i]);
	if(g==1) return cout<<"0\n",0;
	if(n>23) return cout<<"1\n",0;
	for(int i=1;;i++)
		dfs(1,i,0,0);
	return 0;
}
```

---

## 作者：海洋守卫者 (赞：1)

# [P12431](https://www.luogu.com.cn/problem/P12431) [BalticOI 2025] Gingerbread

## 解题思路
容易发现，当 $n$ 越大时，所操作的次数也越少。可以进行分类讨论。

先把 $ans=0$ 的情况判断了。当 $\gcd(a_1,\dots,a_n)=1$ 时，显然不用做任何操作，故 $ans=0$。

当 $n\ge4$ 时，令 $g_i=\gcd(a_1,\dots,a_{i-1},a_{i+1},\dots,a_n)$，会存在两种情况：

- $\forall i\in[1,n], \gcd(g_i,a_i+1)\neq 1$，则需进行任意 $2$ 次操作。
- 否则，仅需进行 $1$ 次操作。

当 $2\le n\le3$ 时，由于个数非常少，可以直接暴力计算。

## 完整代码
```cpp
#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
inline int gcd(int a,int b)
{
	return a%b?gcd(b,a%b):b;
}
const int MAXN=1e6+7;
int n,a[MAXN],f[MAXN],b[MAXN];
int g[MAXN],ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	f[1]=a[1],b[n]=a[n];
	for(int i=2;i<=n;i++)f[i]=gcd(a[i],f[i-1]);
	for(int i=n-1;i;i--)b[i]=gcd(a[i],b[i+1]);
	if(f[n]==1){puts("0");return 0;}
	g[1]=b[2],g[n]=f[n-1];
	for(int i=2;i<n;i++)g[i]=gcd(b[i+1],f[i-1]);
	if(n>3)
	{
		bool k=1;
		for(int i=1;i<=n;i++)if(gcd(a[i]+1,g[i])==1)k=0;
		if(!k)puts("1");
		else puts("2");
		return 0;
	}
	else if(n==2)
	{
		ans=0x7f7f7f7f;
		for(int i=0;i<=100;i++)for(int j=0;j<=100;j++)if(gcd(a[1]+i,a[2]+j)==1)ans=min(ans,i+j);
		printf("%d",ans);
	}
	else{
		ans=0x7f7f7f7f;
		for(int i=0;i<=100;i++)for(int j=0;j<=100;j++)for(int k=0;k<=100;k++)
			if(gcd(a[1]+i,gcd(a[2]+j,a[3]+k))==1)ans=min(ans,i+j+k);
		printf("%d",ans);
	}
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

vp 的时候写挂了以为是结论假了被硬控了好久，最后 B 没调完/ll。

我们猜测答案不会很大，因为考虑当 $n > 8$ 时我们随便选一个数加 $1$ 消去最开始的最大公约数，然后如果出现了新的最大公约数就给第二个数加 $1$ 然后以此类推下去，由于题目范围下一个数至多 $8$ 个不同的质因子并且在上面的过程中一个质因子只会被消去一次所以答案不会很大。

当 $n \leq 8$ 时将两个数调整成最近的质数也可以使得答案不会很大。

不妨令答案上界为 $lim$，考虑枚举 $a_1 + i$ 其中 $i \leq lim$，然后对于 $a_1+i$ 分解质因数，把质因数拎出来跑状压即可，可以对这个 dp 进行一定的剪枝，但是注意不要剪枝挂了以为是结论假了像我这样被硬控太久。

时间复杂度不会分析，但是过了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
const int maxs = (1<<10);
const int maxv = 1e7+114;
int n,a[maxn];
int pr[10],tot;
int dp[maxs],vis[maxs];
int st[maxn];
int lim;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    if(n<=8){
        lim=500;
    }else lim=8;
    for(int i=1;i<=n;i++) cin>>a[i];
    int res=a[1];
    for(int i=2;i<=n;i++) res=__gcd(res,a[i]);
    if(res==1){
        cout<<0<<"\n";
        return 0;
    }
    sort(a+1,a+n+1);
    for(int i=2;i<=n;i++){
        if(a[i]==a[i-1]){
            cout<<1<<"\n";
            return 0;
        }
    }
    int ans=lim;
    for(int i=0;i<=lim;i++){
        int u=a[1]+i;
        vector<int> vec;
        for(int j=1;j*j<=u;j++){
            if(u%j==0){
                    vec.push_back(j);
                    if(u%(u/j)==0&&u/j!=j) vec.push_back(u/j);
            }
        }
        tot=-1;
        sort(vec.begin(),vec.end());
        for(int x:vec){
            if(x==1) continue;
            if(u%x==0){
                pr[++tot]=x;
                while(u%x==0) u/=x;
            }
        }
        tot++;
        for(int v=0;v<(1<<tot);v++) dp[v]=1000,vis[v]=0;
        dp[(1<<tot)-1]=i;
        for(int j=2;j<=n;j++){
            for(int g=0;g<=lim;g++){
                st[g]=0;
                for(int k=0;k<tot;k++){
                    if((a[j]+g)%pr[k]==0) st[g]+=(1<<k);
                }
            }
            for(int v=0;v<(1<<tot);v++){
                if(vis[v]==0){
                    for(int g=0;g+dp[v]<=lim;g++){
                        if(g==0||(v&st[g])!=v) dp[v&st[g]]=min(dp[v&st[g]],dp[v]+g);
                    }
                }
            }
            for(int v=0;v<(1<<tot);v++){
                for(int k=0;k<tot;k++){
                    if((1<<k)&v){
                        if(dp[v-(1<<k)]<=dp[v]) vis[v]=1;
                        else vis[v]=0;
                    }
                }
            }
        }
        ans=min(ans,dp[0]);
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

