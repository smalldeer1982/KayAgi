# 「TPOI-1B」ASPAP

## 题目描述

你有 $n!$ 个长度为 $n$ 的排列，它们已经按照字典序排好了顺序。

请你在字典序顺序中前 $S$ 个排列里寻找一个排列 $p$，使得 $\displaystyle\sum_{i=1}^n\sum_{j=1}^{i}p_j$ 最大。你只需要输出这个最大值即可。

由于答案可能很大，请输出答案对 $998244353$ 取模的结果。


## 说明/提示

【样例 #1 解释】

长度为 $4$ 的排列的前五个分别为：

$1,2,3,4 \to 1+(1+2)+(1+2+3)+(1+2+3+4)=20$

$1,2,4,3 \to 1+(1+2)+(1+2+4)+(1+2+4+3)=21$

$1,3,2,4 \to 1+(1+3)+(1+3+2)+(1+3+2+4)=21$

$1,3,4,2 \to 1+(1+3)+(1+3+4)+(1+3+4+2)=23$

$1,4,2,3 \to 1+(1+4)+(1+4+2)+(1+4+2+3)=23$

最大值为 $23$。

【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$10$|$n\le8$|
|$2$|$10$|$T\le20,n\le16$|
|$3$|$25$|$T\le10^4$|
|$4$|$5$|$S=n!$|
|$5$|$50$|无特殊性质|

对于 $100\%$ 的数据，$1 \le T \le 10^5, 1 \le n \le 10^9, 1 \le S \le \min(n!,10^{18})$。

## 样例 #1

### 输入

```
1
4 5```

### 输出

```
23```

# 题解

## 作者：sunkuangzheng (赞：6)

题目所求式子即为 $\sum \limits_{i=1}^n p_i(n-i+1)$。

注意到字典序前 $S$ 小的排列里，只有最后 $20$ 个位置可能满足 $p_i \ne i$，因为 $20!$ 已经大于 $10^{18}$。

首先求出字典序第 $S$ 小的排列 $q$，然后枚举 $p$ 和 $q$ 的 LCP 长度 $l (l \ge n-20)$，那么此时应当有 $p_{1\sim l} = q_{1 \sim l}$。贪心的，此时 $p_{l+1}$ 应当填写小于 $q_{l+1}$ 的最大数字，后面的数字降序排列。

时间复杂度可以做到 $\mathcal O(T \log^2 n)$，可以进一步使用数据结构优化至 $\mathcal O(T \log n \log \log n)$，但是在该数据范围下是没有必要的。

---

## 作者：Lele_Programmer (赞：4)

# P11748 题解

## 思路

由于 $S \le 10^{18}$，且 $19!<10^{18}<20!$，所以可以自由变动的数字只会出现在最后的 $20$ 个位置里面，也就是说无论 $n$ 多大，它前面特别长一段都只能是 $1,2,3,4,\cdots$ 这样填。

第一直觉是越靠后的排列，表达式的值越大，但这显然是错误的。

假设前面的若干位已经确定不变了，剩余的若干个可以任意改变顺序，那么肯定是让数值较大的放在前面。

但这并不表示：在不能真正做到**完全**降序的时候，更大的数字放前面，所得答案越大。例如对于 $n=4$ 的排列，$1,4,3,2$ 计算得到的结果为 $24$，而 $2,1,3,4$ 只有 $21$。

当第 $i$ 位最大仅能填入剩余数字中第 $k$ 大的那个数，那么填入第 $k-1$ 个及以内，就可以使得 $i+1$ 位及后面的位都可以填入剩余数字的任意排列。例如样例一，第一位只能填 $1$，第二位可以填 $2,3,4$，所以最大一个为 $4$，$4$ 不是满的，意思就是填了 $4$ 剩余的 $2,3$ 在后面两个位置不能任意排列，而如果第二位填了 $2$ 或 $3$，那么剩下的另外两个数均可以任意排列，见样例一解释即可直观看出。

所以对于每一位：求出这一位填剩余数的次大值，后面的每个数将剩余数降序排列后的结果；以及这一位填剩余数的最大值，后面的每个数继续如此计算后得到的最大结果。以上两种情况取最大值返回。

由于 $n$ 很大，不可能从 $1$ 开始枚举，刚刚也说了可能出现变化的位置很少，所以直接从可能出现改变的地方开始搜。

初始的答案就是那些已经跳过的固定的数位，先假设 $n$ 个数都按 $1,2,3,\cdots,n$ 排列，计算 $\sum\limits_{i=1}^{n} i(n-i+1)$，化简后就是 $\frac{n(n+1)(n+2)}{6}$，再把后面几位需要更改的暴力减掉即可。

核心部分我用的是递归，注意特判边界情况，比如剩余数字只剩一个，比如这一位不存在可以取的次大值之类的情况。

## 代码

比较抽象就是了。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c) && c!=EOF) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c) && c!=EOF) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c) && c!=EOF) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int mod=998244353;

int T,n,s,m;
vector<int> vec;
vector<int> q;

void init() {
    vec.emplace_back(0);
    vec.emplace_back(1);
    _rep(i,2,1000) {
        vec.emplace_back(vec.back()*i);
        if (vec.back()>1e18) break;
    }
    m=(int)vec.size()-1;
}

int solve(int i,int s,vector<int>& q) { // ...()()()()
    // cout<<"solve "<<i<<" "<<s<<" "<<vec[i-1]<<"    ";
    // _iter(it,q) writesp(*it);
    // putchar(10);
    if (!i) return 0;
    if (i==1) return q[0];
    if (s<=vec[i-1]) {
        int res=q[0]*i;
        q.erase(q.begin());
        res+=solve(i-1,s,q);
        // cout<<"s<=vec[i-1]: "<<i<<" "<<res<<endl;
        return res;
    }
    int mx=1+s/vec[i-1];
    s%=vec[i-1];
    mx--;
    int res=q[mx-1]*i;
    int j=i-1,pt=(int)q.size()-1;
    while (j) {
        int k=q[pt--];
        if (k==q[mx-1]) k=q[pt--];
        res+=k*j;
        --j;
    }
    if (!s) return res;
    mx++;
    int g=q[mx-1]*i;
    q.erase(q.begin()+mx-1);
    // cout<<"full: "<<i<<" "<<res<<endl;
    res=max(res,g+solve(i-1,s,q));
    return res;
}

int exgcd(int a,int b,int& x,int& y) {
    if (!b) {
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

int inverse(int a) {
    int x,y;
    exgcd(a,mod,x,y);
    x=(x%mod+mod)%mod;
    return x;
}

i32 main() {
    init();
    read(T);
    while (T--) {
        read(n),read(s);
        int i=n-m;
        i=max(i,0LL);
        int ans=(n*(n+1)%mod)*(n+2)%mod;
        ans=ans*inverse(6)%mod;
        _rep(j,i+1,n) {
            ans-=(n-j+1)*j;
            ans=(ans%mod+mod)%mod;
        }
        // cout<<i<<" "<<n-i<<" "<<vec[j]<<" "<<ans<<endl;
        if (n<=m && vec[n]==s) {
            assert(ans==0);
            _rep(i,1,n) ans=(ans+i*i)%mod;
            writeln(ans);
            continue;
        }
        q.clear();
        _rep(k,i+1,n) q.emplace_back(k);
        int res=solve(n-i,s,q);
        res%=mod;
        ans+=res;
        ans%=mod;
        writeln(ans);
    }
    return 0;
}

/*
4
4 5
4 6
4 24
4 17

23
24
30
28
*/
```

---

## 作者：dci66666 (赞：2)

这题竟然才绿啊，亏我调了3个小时。

其实这个题只需要有两个重要的点，其他都是比较简单的对吧：
1. 怎么找到贪心策略。

这个其实也不难，手模一下阳历可以发现，第 $S$ 个答案并不是最优解！这个随便可以举出反例。但是，可以细致的发现，一般将较大数放在较前面是很优的，但可能也会顾此失彼！比如阳历中出现的两种答案相等的情况，如果再在答案中加一个 $5$ 那样的话易证贪心失效。但是也考虑这种贪心也是有合理性的，因为假如没有 $S$ 的限制的话可以随意从大到小排序，直接给出答案。

思考为什么贪心不成立呢？因为 $S$ 的限制。

我们可以分情况讨论，肯定有前一部分排列的最大答案中出现从大到小排序的部分，我们称该排列及之前的部分为不受 $S$ 限制的部分，而后面的部分因为没有办法达到从大到小排列，所以称为受 $S$ 限制的部分。没有 $S$ 限制的部分直接将可排序的部分（怎么定一会儿说）排序得到答案。之后的部分，又该怎么处理？相当于我们又限制了一位（因为当我们考虑时是一位一位考虑的）。直接把得到答案的重任交给下一位，同时减掉本位到达这一位的方案数，因此可以采用递归求解，下一位时再考虑如上操作，直到最后一位。也就是说，要么顶着限制，继续前进，将位数卡满，要么放弃限制，但获得可以直接排序的机会。

~~诶？这不数位dp嘛（类似）。~~

嗯，如果只想到这里的话，那么，恭喜你，这是第一步，但是只想到这，还是远远不够的。

理想很丰满，现实很骨感，你看看那个 $n$ 那是给过的？

2. 优化，优化，还是优化！

我们这个贪心策略，确实是对的，但是复杂度差到家了。有没有更好的方法呢？

观察到 $S$ 的数据范围，还是很小的（小？）。考虑 $20!>10^{18}$ 所以能改变的位不超 $20$ 个！这是个非常重要的性质。所以我们考虑时直接从后二十位考虑就行了。

这个优化已经很好了，但还远远不够 $1e9$ 的零头。毕竟枚举一遍需要很高的时间复杂度！太不友好了！将序列拆成前后两个，前面的肯定是顺序，而后面的是自己贪的。前面那些数，扫一遍都不行。前面不变的数怎么办？难道还能不扫？还真是。

一个顺序序列（假设就是从小到大的），考虑贡献，也无非是 $\displaystyle\sum_{i=1}^n\sum_{j=1}^{i}j$，由等差序列求和公式可知 $\displaystyle\sum_{i=1}^n\sum_{j=1}^{i}j=\displaystyle\sum_{i=1}^n \frac{i\times (i+1)}{2}$ 好像也不明显，再该一下 $\displaystyle\sum_{i=1}^n i\times (i+1)=\displaystyle\sum_{i=1}^n i^2+\displaystyle\sum_{i=1}^n i$ 这就要不得不提一个公式了 $\displaystyle\sum_{i=1}^n i^2=\frac{(2n+1)(n+1)n}{6}$ 了，带入原式 $\displaystyle\sum_{i=1}^n\sum_{j=1}^{i}j=\frac{(2n+1)(n+1)n}{12}+\frac{(n+1)n}{4}$ 这个可以在 $O(1)$ 的时间内实现！虽然实际情况少了一块（后面），但是后面的贡献可以自己计算减掉（按照顺序排列的后面一部分），再加上贪心的答案，完美！

再说说上文说的怎么分前后两个序列呢？先通过遍历，找到 $S$ 恰好小于 $a!$ 的数字，此时，后 $a$ 位就是想要的答案了。至于递归到下一层时，减掉的是从小到大可以所有可以填的数字减掉 $a-1$ 的全排列就行了。~~（这个实现真的恶心。）~~

好了，是时候上代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;//（这里为了省事直接开 __int128）
#define int __int128
int t,mp[25],vis[25];
const int mod=998244353;
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int dfs(int k,int x,int n,bool f,int S,int sum){
	if(x==n){
		//write(f);putchar(' ');write(v[0]);putchar(' ');write(v.size());putchar(' ');write(sum+v[0]);puts("");
		for(int i=0;i<=n-k;i++){
			if(!vis[i])return sum+i+k;
		}
	}
	if(!f){
		int ans=0,tot=0;
		//for(int i=0;i<len;i++)ans+=(i+1)*v[i];
	    for(int i=0;i<=n-k;i++){
	    	if(!vis[i]){
	    		ans+=(++tot)*(k+i);
			}
		}
		//write(x);putchar(' ');write(S);putchar(' ');write(ans);putchar(' ');write(sum);putchar(' ');
	//puts("");
		return sum+ans;
	}
	int ans=0;
	for(int j=0;j<=n-k;j++){
		if(vis[j])continue;
		int i=j+k;
		//for(int j:v)if(i!=j)q.push_back(j);
		vis[j]=1;
		ans=max(ans,dfs(k,x+1,n,(S-mp[n-x]<=0),S,sum+(n-x+1)*i));
		vis[j]=0;
		S-=mp[n-x];
		if(S<=0)break;
	}
	return ans;
}
inline int read(){
	int x=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c<='9'&&c>='0'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x;
}
void solve(){
	int n=read(),S=read(),f=1;
	//write(S);puts("");
	for(int i=n;i>=1;i--){
		int j=n-i+1;
		if(S<mp[j]){
			f=i;break;
		}
		//write(mp[j]);
	}
	//write(f);puts("");
	int ans=0;
	for(int i=f;i<=n;i++){
		//vector<int>v;
		//for(int j=f;j<=n;j++)if(i!=j)v.push_back(j);
		vis[i-f]=1;
		ans=max(ans,dfs(f,f+1,n,(S-mp[n-f]<=0),S,(n-f+1)*i));
		vis[i-f]=0;
		S-=mp[n-f];
		if(S<=0)break;
	}
	int tp1=(n*(n+1)*(2*n+1)/6+n*(n+1)/2)/2;
    //write(tp1);puts("");
	int tp2=0;
	for(int i=f;i<=n;i++){
		tp2+=i*(n-i+1);
	}
	int sum=(ans+tp1-tp2)%mod;
	//write(ans);puts("");
	write(sum);
	puts("");
	return ;
}
signed main(){
	t=read();
	mp[1]=1;
	for(int i=2;i<=21;i++){
		mp[i]=mp[i-1]*i;
	}
    while(t--){
    	solve();
	}
} 
```

---

## 作者：chzhh_111 (赞：1)

我们不难发现，假设在这个序列中第 $i$ 位的数字为 $a_{i}$，故原式可转化为 $\textstyle\sum_{i=1}^{n} a_{i} \times (n - i + 1)$，观察可发现，如果将越大的数放在越前面，那么所贡献的值就会相对比较多，因此我们现在就可以产生一个贪心思路：**将当前能放的数当中最大的放下，然后统计答案**。但是这样子是错误的，我们可以从下面两组序列中看出情况：

1. $10$ $1$ $2$ $3$ $4$ $5$ $6$ $7$ $8$ $9$

2. $9$ $10$ $8$ $7$ $6$ $5$ $4$ $3$ $2$ $1$

很明显，如果当前的 $S$ 在长度为 $10$ 的序列中，为第一个序列的话，那么按照刚刚那个贪心思想下面这个序列很明显不会被考虑，但是第二个序列的价值有很明显大于第一个序列，因此我们一开始的贪心思路就是错的。

同时我们也可以从刚刚的例子当中发现，如果最大的不是最优的选择，那么次大的呢？如果这一位填的是我们所能填的数当中第二大的数，则后面的序列一定是一个降序序列才是最优的，而第三大的数所能填的最优方案肯定比第二大的数的最优方案来得小，因此我们只需要考虑第二大数的和最大的数。

那么经过刚刚的分析，我们再重新确定一下我们的贪心思路：**先寻找出当前所能放下的最大的数，再去求放一下第二大的数所产生的最大价值是多少，如果比我们当前的答案大，则就记录。接下来再填入我们所能放下的最大的数，进入下一位，重复这个过程。将所有的数放完后，再统计一遍答案。**

同时我们可以发现 $20!$ 已经大于我们 $S$ 的最大值了，因此如果 $n$ 大于 $20$ 的话，除去最后的 $20$ 位，前面一定是顺序的，这就意味着我们最多需要考虑最后 $20$ 位放什么就行了。

但是题目要求对最大值取模，那么边取模边统计最大值很明显是一个非常愚蠢的举动，其实最后统计的那 $20$ 位是不会爆 `long long` 的，所以直接计算即可，然后再和前面贡献的值加在一起取模就行了。

代码实现 ~~我个人认为比较难~~：

```cpp
/*rak[i]指的是这个数在当前所能放的数中的排名*/
/*rhk[i]指的是排名是在这个位置的数是什么 */
/*vis[i]指的是这个数有没有被选过*/
/*fac[i]指的是阶乘*/
/*_2指在模998244353的意义下，2的逆元*/
/*_6指在模998244353的意义下，6的逆元*/ 
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=25,mod=998244353,_2=499122177,_6=166374059;
int T,n,S,ans,fac[N],rak[N],rhk[N];bool vis[N];
void clean()
{
	memset(rak,0,sizeof(rak));
	memset(rhk,0,sizeof(rhk));
	memset(vis,0,sizeof(vis));
	ans=0;
}
int F(int x) {return x*(x+1)%mod*_2%mod;}//1+2+3+···+n=F(n) 
int G(int x) {return x*(x+1)%mod*(2*x%mod+1)%mod*_6%mod;}//1^2+2^2+3^2+···+n^2=G(n) 
signed main()
{
	fac[0]=1;
	for(int i=1;i<=20;i++) fac[i]=fac[i-1]*i;
	scanf("%lld",&T);
	while(T--)
	{
		clean();
		scanf("%lld%lld",&n,&S);
		int sum=0;
		int len=min(n,20ll);
		for(int i=n-len+1;i<=n;i++) rak[i-(n-len+1)+1]=i-(n-len+1)+1,rhk[i-(n-len+1)+1]=i;
		for(int i=n-len+1,cnt=len;i<=n;i++)
		{
			int tot,last;
			//tot为最大值，last为次大值。 
			for(int j=len;j>=1;j--)
				if(!vis[j]&&S>fac[n-i]*(rak[j]-1)) {S-=fac[n-i]*(rak[j]-1);vis[j]=1;tot=rhk[rak[j]];last=rhk[rak[j]-1];break;}
			if(last!=0)
			{
				int Sum=sum+last*(n-i+1);
				for(int j=i+1,k=cnt;j<=n&&k>=1;j++,k--)
				{
					if(rhk[k]==last) k--;
					Sum+=rhk[k]*(n-j+1);
				}
				ans=max(Sum,ans);
			}//这里的if语句就是处理次大的情况。
			cnt=0;
			for(int j=1;j<=len;j++)
			{
				if(vis[j]) {rak[j]=0;continue;}
				else cnt++,rak[j]=cnt,rhk[cnt]=(n-len+1)+j-1;
			}
			sum+=tot*(n-i+1);
		}
		ans=max(ans,sum);//所有数放完，再统计。  
		ans%=mod;
		if(n>20)
		{
			int m=n-20;
			ans+=((n+1)%mod*F(m)%mod-G(m)+mod)%mod,ans%=mod;//前面的贡献。  
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：GA34 (赞：1)

贪心好难。。。

看到有大佬 $O(n^3)$ 卡过去了，啧啧称奇

赛时一直在调取第$s$个排列的做法，没看阳历，导致一分没得

看完题解才发现其实这道题并不能纯粹的贪心，特此记录

# 思路

一开始很容易想到一种做法：选取第$s$个排列

但这种做法的错误性在样例中就可以体现

对于样例 $1$ 中 $n=4$ 的排列，$1,4,3,2$ 的结果为 $24$，而 $2,1,3,4$ 为 $21$

但这种思路的其中一部分是没有错误的：

"如果前面的若干位已经确定不变，剩下的可以任意改变顺序，那么改变顺序时，让数值较大的放在前面"

有了这个基础，我们就要思考怎么确定不变的若干位

那么手模一下就可以发现

#### 如果填入当前位可填数的次大值及以内的数

#### 就可以使第 $i$ 位后面的位都可以填入剩余数字的任意排列

所以对于当前位就取两种情况：

1. 求出这一位填入可填数的次大值，后面的每个数将剩余数降序排列后的结果

2. 后面所有位填剩余数的最大值的最大结果

以上两种情况取最大值输出答案即可

---

## 作者：zhoumurui (赞：1)

### 题面展示

找到一个长度为 $n$ 的排列 $p$，满足它在所有长度为 $n$ 的排列中字典序是前 $S$ 小，且 $\displaystyle\sum\limits _{i=1}^{n}\sum\limits_{j=1}^{i}p_j$ 最大。

### 解题思路

非常好数学题，让我的式子旋转。

#### PART 1 简化到 $n \le 20$

首先，$\displaystyle\sum\limits _{i=1}^{n}\sum\limits_{j=1}^{i}p_j = \sum\limits _{i=1}^{n} (n-i+1) \times p_i$ 是显然的。

接下来，由于 $n$ 太大，我们考虑从 $S \le 10^{18}$ 突破。由于 $20! > 10^{18}$，我们发现：

- $S \le 10^{18}$ 且 $p$ 的字典序在所有长度为 $n$ 的排列中前 $S$ 小 $\implies \forall 1 \le i \le n-20，p_i = i$。

即前 $n-20$ 个字符**一定**是固定的，我们只需讨论剩下 $20$ 个。在这之前，我们需要计算前 $n-20$ 个字符对答案的贡献。

**这里是推式子时间！**

我们需要计算 $\displaystyle \sum\limits_{i=1}^{n-20} i \times (n-i+1)$。

- $\displaystyle \sum\limits_{i=1}^{n-20} i \times (n-i+1)$

  $(=\displaystyle \sum\limits_{i=1}^{n} i \times (n-i+1))-(\sum\limits_{i=n-19}^{n} i \times (n-i+1))$

  $(=\displaystyle \sum\limits_{i=1}^{n} i \times (n-i+1))-(\sum\limits_{i=1}^{20} i \times (n-i+1))$

  $(=\displaystyle \sum\limits_{i=1}^{n} i \times (n-i+1))-(\sum\limits_{i=1}^{20} i \times (20-i+1))+20 \times (n-20)$

  令 $f(k)=\displaystyle \sum\limits_{i=1}^{k} i \times (k-i+1)$，

  那么原式 $=f(n)-f(20)+20 \times (n-20)$

那么我们把问题简化成了计算 $f(k)$ 的结果。~~如果你的小学奥数学得很好，你一定已经知道式子了，但可惜我学的不好，所以~~开始推式子。

试图计算找规律，得到 $f(0)=0$，$f(1)=1$，$f(2)=4$，$f(3)=10$，$f(4)=20$。

那么我们可以发挥惊人的注意力，将他们做个差分，得到 $f(1)-f(0)=1$，$f(2)-f(1)=3$，$f(3)-f(2)=6$，$f(4)-f(3)=10$，我们非常熟悉的一串数。

**引理 1** $\displaystyle f(k)-f(k-1) = \frac{k \times (k+1)}{2}$。

**证明** 计算得到：

- $\displaystyle f(k)-f(k-1) = \displaystyle \sum\limits_{i=1}^{k} i \times (k-i+1) - \displaystyle \sum\limits_{i=1}^{k-1} i \times (k-i)$

  $= \displaystyle (\sum\limits_{i=1}^{k-1} i) + k$

  $= \displaystyle \sum\limits_{i=1}^{k} i$

  $= \displaystyle \frac{k \times (k+1)}{2}$

- 于是命题得证。

容易联想到下面引理：

**引理 2** $f(k)=\displaystyle \frac{1}{2} \sum\limits_{i=1}^{k} k(k+1)$。

**证明** 用数学归纳法。

- 当 $k=0$ 时，有 $f(0)=0$ 符合条件。

- 假设 $k=x$ 时符合条件，那么当 $k=x+1$ 时：

  $f(x+1)=f(x)+\displaystyle \frac{(x+1) \times (x+2)}{2}$

  $=\displaystyle \frac{1}{2}( \sum\limits_{i=1}^{x} x(x+1) + \frac{(x+1) \times (x+2)}{2}$

  $=\displaystyle \frac{1}{2} \sum\limits_{i=1}^{x+1} x(x+1)$

  也符合条件。

- 由第一数学归纳法，命题得证。

**结论** $f(k)=\displaystyle \frac{x(x+1)(x+2)}{6}$。

**证明** 简化引理 2 的式子即可。使用小学奥数大佬喜闻乐见的分数裂项。

- $f(k)=\displaystyle \frac{1}{2} \sum\limits_{i=1}^{k} k(k+1)$
  
- $=\displaystyle \frac{1}{2} \sum\limits_{i=1}^{k} \frac{x(x+1)(x+2)-(x-1)x(x+1)}{3}$

- $=\displaystyle \frac{1}{6} (\sum\limits_{i=1}^{k} x(x+1)(x+2) - \sum\limits_{i=0}^{k-1} x(x+1)(x+2))$

- $=\displaystyle \frac{1}{6} k(k+1)(k+2)$

- 于是命题得证。

结合前面的推式子，我们得到：

当 $n=20$ 时，$\displaystyle\text{Ans}_{n,S}= \text{Ans}_{20,S} + \frac{1}{6} n(n+1)(n+2)-\frac{1}{6} \times 20 \times 21 \times 22+20 \times (n-20)$

用了这么长的篇幅，我们成功把问题简化到 $n \le 20$ 的情况。

#### PART 2 解决 $n \le 20$

从一个长度为 $n$ 的排列 $p$ 的字典序编号 $S$ 中可以快速得到很多信息，例如 $p_1 = \displaystyle \lfloor\frac{S-1}{(n-1)!}\rfloor+1$，以及排列 $p_2,\dots,p_n$ 的字典序编号 $S' = (S-1) \mod (n-1)! +1$。

我们只需要这两个信息。对于计算 $Ans(n,S)$，我们可以考虑最优的排列 $p$ 的 $p_1$ 如何取值：

- $p_1 = \displaystyle \lfloor\frac{S-1}{(n-1)!}\rfloor+1$。这时排列 $p_2,\dots,p_n$ 的字典序编号不能超过 $S' = (S-1) \mod (n-1)! +1$，贡献是 $Ans'_{n-1,S'}$，再算上 $p_1$ 的贡献，总贡献是 $p_1 \times n + Ans'_{n-1,S'}$。

  （这里使用 $Ans'$ 是因为如果 $p_1 <n$，会影响后面的贡献。例如 $1,2,\dots,p_1-1,p_1,p_1+1,\dots,n-1$ 的贡献就不等同于 $1,2,\dots,p_1-1,p_1+1,\dots,n$ 的贡献，前者是错误的而后者是正确的。）
- $p_1$ 可以取 $\displaystyle \lfloor\frac{S-1}{(n-1)!}\rfloor$，如果后者的值不小于 $1$。这时 这时排列 $p_2,\dots,p_n$ 可以随意选择，显然递减是最好的选择，可以直接计算贡献。
- 如果 $p_1$ 取到更小的值，一定不优。因为如果将取到 $\displaystyle \lfloor\frac{S-1}{(n-1)!}\rfloor$ 的位置与 $p_1$ 交换，那么得到的新排列一定满足字典序编号不超过 $S$ 而且更优。

那么只需要模拟。使用一个数组 $\text{temp}$ 存储有哪些值是用过的。初始时 $\text{temp}$ 数组全部为 $0$，每次计算出 $p_i$ 能够取到的最大值（是第 $\displaystyle \lfloor\frac{S-1}{(n-1)!}\rfloor+1$ 个满足 $temp_j=0$ 的点），令 $\text{temp}_{p_i}=1$，然后计算下一位。

计算完当 $p_i$ 取到最大值时 $p_{i+1},\dots,p_n$ 的最大答案以后，与 $p_i$ 取到次大值时的答案比较，取较大的回溯到上一位即可。

### 核心代码展示

递归写法常数较大，近 400ms。

```cpp
const int M=998244353;
int ksm(int a,int b){
    if (b==0)return 1;
    if (b&1)return ksm(a,b^1)*a%M;
    int k=ksm(a,b>>1);
    return k*k%M;
}
int f(int x){
    return (x*x%M*x%M+3*x*x%M+2*x)%M*ksm(6,M-2)%M;
}
int fc[25];
vector<int> tmp;
int cal(int m,int s,vector<int> temp){
    //cout<<s<<"\n";
    if (m==0)return 0;
    
    int ans;
    if (m>20){
        ans=cal(20,s,tmp);
        int ex=f(m)-f(20);
        //cout<<m<<" "<<s<<" "<<ans<<"\n";
        return ((ans+ex)%M+M)%M;
    }
    if (s==fc[m]){
        int cnt=0,ans=0;
        for (int j=1;j<=20;j++){
            if (!temp[j]){
                ++cnt;
                ans+=j*cnt;
                if (cnt==m)return ans;
            }
        }
        return ans;
    }
    ans=0;
    int k=(s-1)/fc[m-1]+1,cnt=0,xxx=0;
    for (int j=1;j<=20;j++){
        if (!temp[j]){
            cnt++;
            if (cnt==k-1){
                xxx=j;
            }
        }
        if (cnt==k){
            k=j;
            break;
        }
    }
    temp[k]=1;
    ans=m*k%M;
    int ttt=(s-1)%fc[m-1]+1;
    //cout<<m<<" "<<s<<" "<<ans<<"\n";
    int nxt=cal(m-1,ttt,temp);
    //cout<<m<<" "<<s<<" "<<nxt<<"\n";
    
    if (xxx&&ttt!=fc[m-1]){
        temp[k]=0;
        temp[xxx]=1;
        nxt=max(nxt,cal(m-1,fc[m-1],temp)-m*(k-xxx));
    }
    //cout<<m<<" "<<s<<" "<<nxt<<"\n";
    return (ans+nxt)%M;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i=0;i<=20;i++)tmp.push_back(0);
    cin>>n;
    //n=50000;
    fc[0]=1;
    for (int i=1;i<=20;i++){
        fc[i]=fc[i-1]*i;
        //cout<<i<<" "<<fc[i]<<"\n";
    }
    for (int i=1;i<=n;i++){
        int m,s;
        cin>>m>>s;
        cout<<cal(m,s,tmp)<<"\n";
    }
    return 0;
}
```

---

## 作者：ran_qwq (赞：1)

$S$ 最大是 $10^{18}$，又注意到 $20!>10^{18}$，所以前 $n-20$ 位都是 $p_i=i$。接下来，我们令 $n\leftarrow\min(n,20)$。

显然可以类似数位 dp 一样地状压，但时间复杂度爆炸。

考虑发现一些性质。如果第 $1\sim i-1$ 位顶到了最大值（意思是如果更大超出了字典序前 $S$ 个的限制），而第 $i$ 位没有顶到，那么第 $i+1$ 位以后都可以随便编排。而随便编排的话，倒序排列是最优的。所以实际的状态只有 $n^2$ 种（哪里没顶到最大值，这一位是多少）。再加个处理后面的 $O(n)$，时间复杂度 $O(Tn^3)$，常数较小可以通过。

```cpp
int n,a[N],b[N]; ll s,fc[N],vs[N]; lll as;
void QwQ() {
	n=rd(),s=rdll(),mst(vs,0),as=0; lll ss=s;
	for(int i=min(n,20);i;i--) for(int j=1;j<=n;j++) if(!vs[j]) {
		if(s<=fc[i-1]) {a[i]=j,vs[j]=1; break;}
		s-=fc[i-1];
	}
	for(int i=min(n,20);~i;i--) {
		lll sm=(lll)(n+2)*(n+1)*n/6;
		for(int j=1;j<=min(n,20);j++) sm-=1ll*j*(n-j+1);
		for(int j=min(n,20);j>i;j--) sm+=1ll*j*(a[j]+max(n-20,0));
		if(i) {
			for(int j=1,c=0;j<a[i];j++) if(vs[j]&&ss>fc[i-1]*c) {
				lll s=sm; vs[j]=0,s+=1ll*i*(j+max(n-20,0));
				for(int k=min(n,20),p=i-1;k;k--) if(vs[k]) s+=1ll*p*(k+max(n-20,0)),p--;
				vs[j]=1,as=max(as,s),c++;
			}
		} else as=max(as,sm);
		vs[a[i]]=0;
	}
	wr(as%MOD,"\n");
}
signed main() {
//	freopen("in.in","r",stdin),freopen("out.out","w",stdout);
	fc[0]=1; for(int i=1;i<=20;i++) fc[i]=fc[i-1]*i;
	int T=rd(); while(T--) QwQ();
}
```

---

## 作者：Imerance1018 (赞：1)

### Description

[传送门](https://www.luogu.com.cn/problem/P11748)

### Solution

不妨设 $pos$ 为变化的位数，则有 $(pos-1)! \le s$ 且 $pos!>s$。

因为 $20! > 10^{18}$，所以 $pos \le 20$。

注意到 $1+(1+2)+(1+2+3)+...+(1+2+3+...+n)=\frac{n(n+1)(n+2)}{6}$，那么便可以 $O(1)$ 处理出前 $n-pos$ 位的和。

剩下的 $pos$ 位可采取如下策略选取：
1. 选取可选取的最大值（最后会选出来第 $s$ 个排列）。
2. 上面的贪心方法是有反例的，如 ${2,1,3,4}$ 显然没有 ${1,4,3,2}$ 优，因为我们为了满足构造的排列序号小于 $s$，而不得不舍弃一些贡献。此时，我们可以取当前的次大值，类似数位 DP，则剩下的就确定了，直接把没选过的从大到小排列即可。

最后取两种策略的最大值输出。

### Code
```cpp#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int t;
int n,s;
int getsum(int x)//1*2+2*3+3*4+...+x*(x+1)
{
	return x*(x+1)%mod*(x+2)%mod*166374059%mod;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		int pos=1,ji=1;
		for(;pos<=n;pos++)
		{
			ji*=pos;
			if(ji*(pos+1)>s)
			{
				break;
			}
		}
		pos++;
		int ans=getsum(n-pos),lans=0;
		int vis[21]={0},res[21]={0};
		for(int i=1;i<pos;i++)
		{
			int tmp=(s+ji-1)/ji;//最大值的排名（不是最大值）
			int lst=0,jj=0;
			for(int j=1;j<=pos;j++)
				if(vis[j]==0)
				{
					jj++;
					if(jj==tmp-1)
					{
						lst=j;
						break;
					}
				}//选出次大值
			if(lst!=0)//策略 2
			{
				int vis2[21]={0};
				for(int j=1;j<=pos;j++)vis2[j]=vis[j];
				vis2[lst]=1;
				res[i]=lst+n-pos;
				int cnt=i,temp=ans,sum=(n-pos)%mod*(n-pos+1)%mod*499122177%mod;
				for(int j=pos;j>=1;j--)if(vis2[j]==0)res[++cnt]=j+n-pos;
				for(int j=1;j<=pos;j++)
				{
					ans=(ans+(sum+res[j])%mod)%mod;
					sum=(sum+res[j])%mod;
				} 
				lans=max(lans,ans);
				ans=temp;
				for(int j=i;j<=pos;j++)res[j]=0;
			}
			jj=0;
			for(int j=1;j<=pos;j++)
				if(vis[j]==0)
				{
					jj++;
					if(jj==tmp)
					{
						res[i]=j+n-pos;
						vis[j]=1;
						break; 
					} 
				}
			if(ji!=0)s%=ji;
			if(s==0)s+=ji;//注意特判
			ji/=(pos-i);
		}
		for(int i=1;i<=pos;i++)
		{
			if(vis[i]==0)
			{
				res[pos]=i+n-pos;
				break;
			}
		}
		int sum=(n-pos)%mod*(n-pos+1)%mod*499122177%mod;
		for(int i=1;i<=pos;i++)
		{
			ans=(ans+(sum+res[i])%mod)%mod;
			sum=(sum+res[i])%mod;
		}
		lans=max(lans,ans);
		cout<<lans<<endl;
	}
	return 0;
}
``````

---

## 作者：MPLN (赞：0)

大胆猜测最大排列就是字典序第 S 个排列
```cpp
for (int i = n, hv = 0, a = s, j; i; i--) { // 求最大字典序排列
    for (j = 1; j <= n; j++) {
        if (hv & (1 << j - 1)) continue;
        if (a - jc[i - 1] > 0) a -= jc[i - 1]; // jc[i]为i的阶乘
        else break;
    }
    hv |= 1 << j - 1, num[i] = j;
}
```
显然，这是错的。

举例，$n=5$，$S=19$，第 19 个排列为 $15234$， $val=41$，但是第 18 个排列 $14532$ 的 $val=44$。

接下来探索性质，发现当 $n=20$，$n!>10^{18}$ ，而如果要改变某个数从低到高第 21 位，必须先用完 $20!$ 个后续排列情况，而这是不可能的，因为 $S\le 10^{18}$ ，因而所有大于 20 位的排列前 $n-20$ 位都是固定的。我们设 $k=n-20$ ,则该数字表现为：

$$
1,2,3\dots(k-1),k,\underbrace{\text{xxx\dots xxx}}_{\text{20位}}
$$

后面 20 位是对于 $n=20$ 的第 $S$ 个排列，每一位都加上 $k$ 的结果。

接下来想想如何求 $n\le 20$ 的答案，我们可以用数位 DP ，先求出（第 $S$ 个）字典序最大排列 $A$ ，然后**以 $A$ 为限制从高到低位**记忆化搜索所有情况，不难发现这个复杂度是 $O(2^n)$ 的，对于 $T\le 10^5$ 难以接受。

考虑剪枝，当 $lim=0$ ，即已经不受 $A$ 的限制，后面能随便选。则对于后面几位没有填充的，直接从大到小遍历所有没选的 n ~ 1 数字填上即可。

接下来推导将 $n=20$ 应用到我们要的 $20<n \le 10^9$ 的情况，因为 $n$ 是在太大，一位一位增加是不行的，需要求一个通用公式！

分为 2 部分计算增加的分值 $d$ ，分别是：后 20 位每一位增加 $k$ 后增值乘上权重的增加总和 $a$ ，和前面新的 $123...k$ 每一位再乘上权重的的结果 $b$。

易得 $a=k\sum_{i=1}^{20}i=210k$

再化简 $b$ ：

$$
\begin{aligned}
b&=\sum_{i=1}^{k}i(21-i+k)\\
&=\sum_{i=1}^{k}(21i-i^2)+k\sum_{i=1}^{k}i\\
&=(21+k)\sum_{i=1}^{k}i-\sum_{i=1}^{k}i^2\\
&= (21+k) \cdot \frac{k(k+1)}{2} - \frac{k(k+1)(2k+1)}{6}\\
&= \frac{k(k+1)(k+62)}{6}
\end{aligned}
$$

至此问题解决！奉上代码：

时间复杂度上界是 $O(aT)$ ，其中 $a$ 是跑 $n=20$，$S=10^{18}$ 的最优排列复杂度，这个~~我也懒得算~~是大概 1000 次枚举，是稳过的。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int t, n, s, ans, jc[21], num[21], mem[21][1 << 20];
int dfs(int sum, int x, int hv, bool lim) { 
    //暴力搜索，lim是有没有受到最大排列限制，即是否不能随便排，似数位DP
    if (!x || !lim) { // 后面可任意选择，贪心剪枝
        if(mem[n][hv] != -1) return mem[n][hv] + sum;
        mem[n][hv] = 0;
        for (int i = n; i; i--) {
            if (hv & (1 << i - 1)) continue;
            mem[n][hv] += x * i, x--;
        }
        return mem[n][hv] + sum;
    }
    int mx = -1;
    for (int i = 1; i <= num[x]; i++) {
        if (hv & (1 << i - 1)) continue;
        mx = max(mx, dfs(sum + x * i, x - 1, hv | (1 << i - 1), i == num[x]));
    }
    return mx;
}
signed main() {
    memset(mem, -1, sizeof(mem));
    jc[0] = jc[1] = 1;
    for (int i = 2; i <= 20; i++)
        jc[i] = jc[i - 1] * i; // 预处理i!
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &s);
        // S最多1e18，只用考虑后21位的答案，前面是固定的1234...
        int tmp = n; n = min(n, 20LL);
        for (int i = n, hv = 0, a = s, j; i; i--) { // 求最大字典序排列
            for (j = 1; j <= n; j++) {
                if (hv & (1 << j - 1)) continue;
                if (a - jc[i - 1] > 0) a -= jc[i - 1];
                else break;
            }
            hv |= 1 << j - 1, num[i] = j;
        }
        ans = dfs(0, n, 0, 1);
        if (tmp > n) { // 如果n较大，可以用公式加速累加
            int k = (tmp - n) % mod;
            // 以下就是在算公式加在答案上，有点乱建议自己写一遍
            ans = (ans + 210 * k % mod) % mod;
            int x = (k * (k + 1)) / 2, y = (62 + k);
            if (x % 3 == 0) x /= 3; else y /= 3;
            x %= mod, y %= mod;
            ans = (ans + x * y % mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```
~~话说是不是有点像蓝题题解awa~~

---

