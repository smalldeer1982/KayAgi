# [SDCPC 2023] Difficult Constructive Problem

## 题目描述

给定一个长度为 $n$ 的字符串 $s_1s_2\cdots s_n$，其中 $s_i \in \{\text{0}, \text{1}, \text{?}\}$，另外给定一个整数 $k$，请将字符串中所有的 $\text{?}$ 换成 $\text{0}$ 或 $\text{1}$，使得满足 $1 \le i < n$ 且 $s_i \ne s_{i+1}$ 的下标 $i$ 恰有 $k$ 个。不同的 $\text{?}$ 可以用不同字符替换。

为了让这题变得更加困难，我们要求您在答案存在的情况下，输出字典序最小的答案。

请回忆：称长度为 $n$ 的字符串 $a_1a_2\cdots a_n$ 的字典序小于长度为 $n$ 的字符串 $b_1b_2\cdots b_n$，若存在一个整数 $k$（$1 \le k \le n$）使得对于所有 $1 \le i < k$ 有 $a_i = b_i$，且 $a_k < b_k$。

## 样例 #1

### 输入

```
5
9 6
1?010??01
9 5
1?010??01
9 6
100101101
9 5
100101101
9 3
????????1
```

### 输出

```
100100101
Impossible
100101101
Impossible
000000101
```

# 题解

## 作者：Coffee_zzz (赞：6)

首先发现在字符串开头或末尾的 $\texttt{?}$ 不好考虑，那我们就特殊判断，把 $\texttt{?}$ 拆成 $\texttt{0}$ 和 $\texttt{1}$。

接下来，我们求出把 $s$ 中的每一个 $\texttt{?}$ 都修改后，满足条件的下标的数量的下限 $a$ 和上限 $b$。当不满足 $a \le k \le b$ 时显然无解。

同时，由于把一个原本是 $\texttt{?}$ 的位置从 $\texttt{1}$ 修改为 $\texttt{0}$ 或从 $\texttt{0}$ 修改为 $\texttt{1}$，满足条件的下标的数量会加减 $2$ 或不变。所以，当 $a$ 和 $k$ 的奇偶性不同时也无解。当然，显然地，$a$ 和 $b$ 的奇偶性一定是相同的，所以我们不需要考虑 $b$ 和 $k$ 的奇偶性。

这样就判断完无解的条件了，接下来我们考虑构造。

我们首先把所有的 $\texttt{?}$ 都修改为 $\texttt{0}$，此时字典序最小，求出满足条件的下标的数量 $cnt$。

当 $cnt=k$ 时，答案合法且最优，直接输出即可。

当 $cnt \gt k$ 时，我们要减少相邻两个元素不同的数量，把一些 $\texttt{?}$ 从 $\texttt{0}$ 修改为 $\texttt{1}$。

当 $cnt \lt k$ 时，我们要减少增加两个元素不同的数量，还是要把一些 $\texttt{?}$ 从 $\texttt{0}$ 修改为 $\texttt{1}$。

为了使答案的字典序尽可能小，我们贪心地从右往左修改。注意，有些时候一些修改是没有用的，我们不能进行这些修改。

最后，直接输出修改完的字符串 $s$ 即可。


---

## 作者：Larryyu (赞：4)

## _Description_
有一个长度为 $n$ 的 ```01``` 字符串 $s$，其中部分位置已给出，在 ```?``` 的位置处需填入一个 ```1``` 或 ```0```。

一个填充方案是好的，当且仅当存在 $m$ 个不同的 $i$ 满足 $1\le i<n$ 且 $s_i\ne s_{i+1}$。

求所有好的填充方案中字典序最小的一个，如果无解输出 ```Impossible```。

对于两个长度为 $n$ 的字符串 $a,b$，若存在一个整数 $k(1\le k\le n)$，使得所有 $1\le i<k$ 有 $a_i=b_i$ 且 $a_k<b_k$，则称 $a$ 的字典序小于 $b$ 的字典序。
## _Solution_
设当前 有 $w$ 个 $i$ 满足 $1\le i<n$ 且 $s_i\ne s_{i+1}$。

引理：对于 $1<i<n$，将 $s_i$ 取反，$w$ 的奇偶性不变，分类讨论证明：

- $101\rightarrow111,w=w-2$
- $111\rightarrow101,w=w+2$
- $010\rightarrow000,w=w-2$
- $000\rightarrow010,w=w+2$
- $100\rightarrow110,w=w$
- $110\rightarrow100,w=w$
- $011\rightarrow001,w=w$
- $001\rightarrow011,w=w$

### _Sol1_
只有将 $s_1$ 或 $s_n$ 取反才能将 $w$ 改变奇偶性。

所以将 $s_1$ 和 $s_n$ 固定后就不用考虑 $w$ 的奇偶性。

对于整个字符串，一定存在 $w$ 能取到的最大值和最小值，设分别为 $w_1,w_2$。

由引理得 $2\mid w_1-w_2$，所以当 $2\nmid m-w_2$ 时，合法填充一定无法做到 $w=m$，输出 ```Impossible```。

如何求出 $w_1$ 和 $w_2$ 呢？

我们用 $e$ 数组记录下一段连续的 ```?``` 的左端点 $l$ 和右端点 $r$，这里的端点指两边第一个不是 ```?``` 的字符。

对于一段 ```?```，我们分类讨论，其中 $len$ 表示这一段 ```?``` 的个数：

- $l=r$，在全都填与左右端点相同时取到 $w_2=0$，当 $2\mid len$ 时，$w_1=len$，否则 $w_1=len+1$

- $l\ne r$，在全都填与左右端点其中一个时取到 $w_2=1$，当 $2\mid len$ 时，$w_1=len+1$，否则 $w_1=len$

可以在纸上举几个例子找规律。

我们用一个 $b$ 数组记下字符串中为 ```?``` 的下标。

为了使答案字典序最小，我们先将所有 ```?``` 填上 ```0```，算出此时的 $w$。

若 $w=m$，直接输出当前字符串。

否则说明我们需要把某些 ```0```（在 $b$ 里面的）改为 ```1```。

因为是改为 ```1```，所以字典序会增大，所以从后往前修改保证字典序更优。

设当前要修改第 $i$ 位。

对于修改前 $w<m$ 的情况，分三种情况讨论：

- 若 $s_{i-1}=s_i=s_{i+1}$ ，此时修改 $s_i$，$w$ 会加二，所以修改。

- 若 $s_{i-1}=s_{i+1}\ne s_i$，此时修改 $s_i$，$w$ 会减二，不仅离答案越远，字典序也变大，所以不修改。

- 若 $s_{i-1}\ne s_{i+1}$，此时修改 $s_i$，$w$ 不变，但字典序变大，所以不修改。

对于修改前 $w>m$ 的情况，只有一种情况。因为能修改的改完后只能是 ```1```，所以只有当 $s_{i-1}=s_{i+1}=1$ 时，修改后 $w$ 才会减二。 

在修改前，我们已经记录了每一个连续 ```?``` 的段的左端点和右端点，若一段的左右端点都是 ```1```，则将这一整段 ```?``` 都改为 ```1```。
### _Code1_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int num[1000010];
int a[1000010];
int b[1000010];
int tot,cnt;
bool f=0;
int maxn,minn;
struct node{
	int l,r;
}e[1000010];
void clean(){  //多测清空
	tot=cnt=f=0;
}
void print(){
	for(int i=1;i<=n;i++){
		cout<<a[i];
	}
	cout<<endl;
}
void solve(int x,int y,int z,int w){
	maxn=0,minn=0;
	for(int i=1;i<=n;i++){
		a[i]=num[i];
	}
	if(x){
		a[x]=y;
	} 
	if(z){
		a[z]=w;
	}
	for(int i=1;i<n;i++){
		if(a[i]!=a[i+1]&&a[i]!=2&&a[i+1]!=2){  //不是?的连续段，w1和w2是确定的
			minn++;
			maxn++;
		}
	}
	for(int i=1;i<=cnt;i++){
		int len=e[i].r-e[i].l-1;  
		maxn+=len;
		if(a[e[i].l]==1&&a[e[i].r]==1) maxn+=(len%2==1)?1:0;
		else if(a[e[i].l]==0&&a[e[i].r]==0) maxn+=(len%2==1)?1:0;
		else maxn+=(len%2==1)?0:1,minn+=1;
	}
	if(m<minn||m>maxn||(m-minn)%2!=0){
		return;
	}
	int now=0;
	for(int i=1;i<=tot;i++){
		a[b[i]]=0;
	}
	for(int i=1;i<n;i++){
		if(a[i]!=a[i+1]) now++;
	}
	if(now==m){
		print();
		f=1;
		return ;
	}
	if(now<m){
		for(int i=tot;i>=1;i--){
			if(now==m){
				print();
				f=1;
				return ;
			}
			if(a[b[i]+1]==0&&a[b[i]-1]==0){
				a[b[i]]=1;
				now+=2;
			}
		}
		if(now==m){
			print();
			f=1;
		}
		return ;
	}
	if(now>m){
		for(int i=cnt;i>=1;i--){
			if(now==m){
				print();
				f=1;
				return ;
			}
			if(a[e[i].l]==1&&a[e[i].r]==1){
				for(int j=e[i].l+1;j<e[i].r;j++){
					a[j]=1;
				}
				now-=2;
			}
		}
		if(now==m){
			print();
			f=1;
		}
		return ;
	}
}
void sol(){
	clean();
	cin>>n>>m;
	string s;
	cin>>s;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='?') num[i]=2;
		else num[i]=s[i-1]-'0';
	}
	bool ff=0;
	int last=1;
	for(int i=2;i<n;i++){	
		if(num[i]==2){  //将?的下标存起来
			b[++tot]=i;
			ff=1;
		}else{
			if(ff){
				e[++cnt].l=last;  //记录?连续段的左端点和右端点
				e[cnt].r=i;  //注意，这里的端点实际上并不是?，是?外的第一个点
			}
			last=i;
			ff=0;
		}
	}
	if(ff){
		e[++cnt].l=last;
		e[cnt].r=n;
	}
	if(num[1]==2&&num[n]==2){  //枚举字符串两端的情况
		solve(1,0,n,0);
		if(f) return ;  //一旦满足条件，直接输出，此时字典序最小
		solve(1,0,n,1);
		if(f) return ;
		solve(1,1,n,0);
		if(f) return ;
		solve(1,1,n,1);
		if(f) return ;
		printf("Impossible\n");
		return ;
	}
	if(num[1]==2){
		solve(1,0,0,0);
		if(f) return ;
		solve(1,1,0,0);
		if(f) return ;
		printf("Impossible\n");
		return ;
	}
	if(num[n]==2){
		solve(0,0,n,0);
		if(f) return ;
		solve(0,0,n,1);
		if(f) return ;
		printf("Impossible\n");
		return ;
	}
	solve(0,0,0,0);
	if(f) return ;
	printf("Impossible\n");
}
int main(){
	cin>>t;
	while(t--){
		sol();
	}
	return 0;
}
```
这一种解法代码量大，细节多，所以接下来介绍一种更简洁的做法。
### _Sol2_
设 $maxn_{i,j}$ 表示第 $j$ 位为 $i$ 时，$s_{j\sim n}$ 的 $w_1$ 值， $minn_{i,j}$ 表示第 $j$ 位为 $i$ 时，$s_{j\sim n}$ 的 $w_2$ 值。

所以若 $s_j$ 能填 $i$，当且仅当 $minn_{i,j}\le res\le maxn_{i,j}$ 且 $2\mid res-mi$（$s_n$ 为 ```?``` 时例外，因为可以改奇偶性）。注意：这里没有考虑 $s_j$ 本身是否为 ```?```，具体原因往下看。

根据定义，得出 $maxn,minn$ 的递推式：

- $maxn_{i,j}=\max(maxn_{i,j+1},maxn_{1-i,j+1}+1)$

- $minn_{i,j}=\min(minn_{i,j+1},minn_{1-i,j+1}+1)$

递推时从 $n$ 推向 $i$。

当 $s_j$ 不为 ```?``` 时，将 $maxn_{1-s_j,j}=1\times 10^8,minn_{1-s_j,j}=-1\times 10^8$，这样就能保证上面判断 $s_j$ 能否填 $i$ 时，填 $1-s_j$ 肯定不合法。

如果 $s_1$ 既不能填 ```0``` 也不能填 ```1```，输出 ```Impossible```，因为第一位什么都不能填，肯定不满足条件，但如果第一位可以填，就说明存在合法解，后面就不用再判无解。

然后一位位的判能否填 ```0```，不能就填 ```1```。
### _Code2_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m;
int a[1000010];
int maxn[2][1000010],minn[2][1000010]; //第j位为i时的最大最小值 
bool check(int x,int y){
	int cnt=m;
	if(x>1&&y!=a[x-1]) cnt--; //和前面一位不同时，w加了1，所以这里要减1
	if(cnt<minn[y][x]||cnt>maxn[y][x]) return 0;
	if(a[n]!=2&&(cnt-minn[y][x])%2==1) return 0;
	return 1; 
}
void clean(){
	for(int i=1;i<=n;i++){
		maxn[0][i]=maxn[1][i]=0;  //多测清空
		minn[0][i]=minn[1][i]=0;
	}
}
void solve(){
	clean();
	cin>>n>>m;
	string s;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='?') a[i+1]=2;
		else a[i+1]=s[i]-'0';
	}
	for(int i=n;i>=1;i--){
		maxn[0][i]=max(maxn[0][i+1],maxn[1][i+1]+1); 
		minn[0][i]=min(minn[0][i+1],minn[1][i+1]+1);
		maxn[1][i]=max(maxn[1][i+1],maxn[0][i+1]+1);
		minn[1][i]=min(minn[1][i+1],minn[0][i+1]+1);
		if(i==n) maxn[1][i]=minn[1][i]=maxn[0][i]=minn[0][i]=0; //特判i==n
		if(a[i]==0){
			minn[1][i]=100000000;
			maxn[1][i]=-100000000;
		}else if(a[i]==1){
			minn[0][i]=100000000;
			maxn[0][i]=-100000000;
		}
	}
	if(check(1,0)==0&&check(1,1)==0){
		cout<<"Impossible"<<endl;
		return ;
	}
	for(int i=1;i<=n;i++){
		if(check(i,0)) a[i]=0;
		else a[i]=1;
		if(i>1&&a[i]!=a[i-1]) m-=1;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i];
	}
	cout<<endl;
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：Lotus_Land (赞：1)

设满足 $1\leq i< n$ 且 $s_i\not=s_{i+1}$ 的 $i$ 的个数为 $cnt$。

注意到若一个字符不在开头或结尾，那么反转这个字符造成的 $cnt$ 的变化一定是 $0$ 或 $2$。若字符在开头或结尾，则会造成 $cnt$ 奇偶性的变化，比较难以处理。所以枚举开头和结尾字符的 $2^2$ 种情况，再对每种情况分别讨论。

对于给定的一个字符串，容易求出 $cnt$ 的下限 $l_1$ 和上限 $l_2$。如果 $m$ 不在 $[l_1,l_2]$ 这个范围内，或 $l_1,l_2$ 的奇偶性与 $m$ 不同，则为无解。

从前往后贪心，如果一个不确定的位置能填 $\texttt{0}$，那就填 $\texttt{0}$，如果不行，再尝试填 $\texttt{1}$，如果还不行，则为无解。

判断某个位置是否能填 $\texttt{0}$ 或 $\texttt{1}$，只要重新计算 $l_1$ 和 $l_2$，判断是否合法即可。


```cpp
#include<bits/stdc++.h>
#define LL long long
#define ull unsigned long long
#define fir first
#define sec second
#define mkpr make_pair
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
using namespace std;
inline LL read() {
    LL x=0;
    bool t=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')t|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
    return t?-x:x;
}
const int N=1000006;
int n,m;
string s,st;
int a[N];
int calc1(int l,int r) {
    if(l>r)return 0;
    return (s[l-1]!=s[r+1]);
}
int calc2(int l,int r) {
    if(l>r)return 0;
    if((r-l+1+(s[l-1]!=s[r+1]))&1)return r-l+2;
    return r-l+1;
}
bool check(int l,int r) {
    if((s[1]=='0'+l||s[1]=='?')&&(s[n]=='0'+r||s[n]=='?')) {
        s[1]='0'+l;
        s[n]='0'+r;
        for(int i=n-1; i>=1; i--) {
            if(s[i]=='?') {
                if(s[i+1]=='?')a[i]=a[i+1];
                else a[i]=i;
            } else a[i]=0;
        }
        int lim1=0,lim2=0;
        for(int i=1; i<=n; i++) {
            if(s[i]=='?'&&s[i-1]!='?') {
                lim1+=calc1(i,a[i]);
                lim2+=calc2(i,a[i]);
            }
            if(i!=1&&s[i]!='?'&&s[i-1]!='?'&&s[i]!=s[i-1]) {
                lim1++;
                lim2++;
            }
        }
        if(lim1>m||lim2<m)return 0;
        if((m-lim1)%2||(m-lim2)%2)return 0;
        for(int i=2; i<n; i++) {
            if(s[i]=='?') {
                int t1=lim1,t2=lim2;
                t1-=calc1(i,a[i]);
                t2-=calc2(i,a[i]);
                s[i]='0';
                t1+=calc1(i+1,a[i]);
                t2+=calc2(i+1,a[i]);
                if(s[i]!=s[i-1])t1++,t2++;
                if(s[i+1]!='?'&&s[i]!=s[i+1])t1++,t2++;
                if(m>=t1&&m<=t2&&(m-t1)%2==0&&(m-t2)%2==0) {
                    lim1=t1;
                    lim2=t2;
                } else {
                    t1=lim1,t2=lim2;
                    t1-=calc1(i,a[i]);
                    t2-=calc2(i,a[i]);
                    s[i]='1';
                    t1+=calc1(i+1,a[i]);
                    t2+=calc2(i+1,a[i]);
                    if(s[i]!=s[i-1])t1++,t2++;
                    if(s[i+1]!='?'&&s[i]!=s[i+1])t1++,t2++;
                    if(m>=t1&&m<=t2&&(m-t1)%2==0&&(m-t2)%2==0) {
                        lim1=t1;
                        lim2=t2;
                    } else {
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}
int T;
int main() {
	cin>>T;
    while(T--) {
        cin>>n>>m>>st;
        st=" "+st;
        bool flg=0;
        for(int i=0; i<=1; i++) {
            for(int j=0; j<=1; j++) {
                s=st;
                if(check(i,j)) {
                    cout<<s.substr(1,n);
                    flg=1;
                    break;
                }
            }
            if(flg)break;
        }
        if(!flg)cout<<"Impossible";
        cout<<"\n";
    }
    return 0;
}

```

---

