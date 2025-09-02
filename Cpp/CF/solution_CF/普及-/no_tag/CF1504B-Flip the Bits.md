# Flip the Bits

## 题目描述

There is a binary string $ a $ of length $ n $ . In one operation, you can select any prefix of $ a $ with an equal number of $ 0 $ and $ 1 $ symbols. Then all symbols in the prefix are inverted: each $ 0 $ becomes $ 1 $ and each $ 1 $ becomes $ 0 $ .

For example, suppose $ a=0111010000 $ .

- In the first operation, we can select the prefix of length $ 8 $ since it has four $ 0 $ 's and four $ 1 $ 's: $ [01110100]00\to [10001011]00 $ .
- In the second operation, we can select the prefix of length $ 2 $ since it has one $ 0 $ and one $ 1 $ : $ [10]00101100\to [01]00101100 $ .
- It is illegal to select the prefix of length $ 4 $ for the third operation, because it has three $ 0 $ 's and one $ 1 $ .

Can you transform the string $ a $ into the string $ b $ using some finite number of operations (possibly, none)?

## 说明/提示

The first test case is shown in the statement.

In the second test case, we transform $ a $ into $ b $ by using zero operations.

In the third test case, there is no legal operation, so it is impossible to transform $ a $ into $ b $ .

In the fourth test case, here is one such transformation:

- Select the length $ 2 $ prefix to get $ 100101010101 $ .
- Select the length $ 12 $ prefix to get $ 011010101010 $ .
- Select the length $ 8 $ prefix to get $ 100101011010 $ .
- Select the length $ 4 $ prefix to get $ 011001011010 $ .
- Select the length $ 6 $ prefix to get $ 100110011010 $ .

In the fifth test case, the only legal operation is to transform $ a $ into $ 111000 $ . From there, the only legal operation is to return to the string we started with, so we cannot transform $ a $ into $ b $ .

## 样例 #1

### 输入

```
5
10
0111010000
0100101100
4
0000
0000
3
001
000
12
010101010101
100110011010
6
000111
110100```

### 输出

```
YES
YES
NO
YES
NO```

# 题解

## 作者：_Anchor (赞：5)

## Problem

给定两个 01 串，可以选择一些位置，然后分别前缀取反，这些位置满足条件：前缀 0 和 1 的个数相等，询问经过若干次变换能不能使得第一个串变化成第二个串。

## Solution

首先，根据异或的性质，我们很容易发现如果一个位置我们选择偶数次操作，那就是没有意义的，如果是奇数次，那全部都跟操作一次等价。

那么相当于我们这样想：对于每一个不同的位置，它以及它后面的位置被选的总次数必须是奇数次，而对于相同的位置则必须是偶数次。

（也就是一个必须被取反，一个必须不能被取反。）

那么从前往后显然不好考虑，因为我们不知道后面的点被选择的次数，于是我们可以考虑从后往前贪心。

我们考虑记一个变量为 $now$ 表示当前点之后的位置被我们选择了（奇数/偶数）次。（$true$ 为奇数。）

然后讨论当前点的两种情况：

如果相同，那么如果 $now$ 为 $true$，则当前点必选，因为我们要让当前点被覆盖到的次数为偶数才行，如果 $now$ 为 $false$ ，那不管。

如果不同，那么如果 $now$ 为 $true$，则当前点不选，因为我们要让当前点被覆盖到的次数为奇数，如果 $now$ 为 $false$ ，那当前点必选，因为我们要使得当前这个位置的后缀被选次数和是个奇数才能使得这一位反过来。

那么我们考虑求出所有必选位置怎么判无解：

先预处理每一个位置可不可选，然后和看必选位置是不是这个可选位置的子集即可。

这样做只有遍历一次的复杂度，所以时间复杂度 $O(n)$ 。

最后，代码也不难给出。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch))  x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
#define ll long long
const int N=3e5+5,M=1e6+5,INF=1e9+7;
int n,m,q,T,t,Ans;
int a[N],b[N];
char str1[N],str2[N];
int main(){
	read(T);
	while(T--){
		read(n);int sum=0,now=0;bool flag=0;
		scanf("%s",str1+1),scanf("%s",str2+1);
		for(int i=1;i<=n;i++){
			a[i]=b[i]=0;
			sum+=(str1[i]=='1'?1:-1);
			if(sum==0) a[i]=true;
			if(str1[i]!=str2[i]) b[i]=true;
		}
		for(int i=n;i>=1;i--){
			if(b[i]^now){
				if(a[i]) now^=1;
				else flag=true;
			}
		}
		if(flag) puts("NO");
		else puts("YES");
	}
    return 0;
}
```


---

## 作者：听取MLE声一片 (赞：2)

这个题目的关键点是：在区间 $1-n$ 中进行变换。

另外一个关键点是，只有 $01$ 个数相同才可以变换，所以说变换不改变 $01$ 的数量，由此可得可以预处理出每一个可以变换的点。

最后一个点是，靠前的点可能会被变换多次，所以我采用从后往前处理，如果一个数不与 `b` 符合且不能变换直接输出 `NO` 。

从后往前的变换次数用一个数累加即可，不需要一次变换全部更改。

所以综合复杂度为 $O(N)$ 。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a[300001],b[300001],c[300001];
int n,t;
int main()
{
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			char x;
			cin>>x;
			a[i]=x-'0';
		}
		for(int i=1;i<=n;i++){
			char x;
			cin>>x;
			b[i]=x-'0';
		}
		int s1=0,s2=0;
		for(int i=1;i<=n;i++){
			c[i]=0;
			if(a[i]==0)
				s1++;
			if(a[i]==1)
				s2++;
			if(s1==s2)
				c[i]=1;
		}
		int pd=1,sum=0;
		for(int i=n;i>=1;i--){
			if(!pd)
				break;
			a[i]=(a[i]+sum)%2;
			if(c[i]==0){
				if(a[i]!=b[i]){
					pd=0;
					cout<<"NO\n";
				}
				continue;
			}
			else{
				if(a[i]!=b[i])
					sum++;
			}
		}
		if(pd)
			cout<<"YES\n";
	}
	return 0;
}

```

谢谢大家！

---

## 作者：nalemy (赞：2)

## 题意简述

有一个操作：找到 $a$ 中一个前缀，使得它满足其中`0`和`1`的个数相等，将这个前缀中所有数翻转（`0`变成`1`，`1`变成`0`）。

求能否通过若干次操作使 $a$ 变成 $b$。

## 做法分析

Q：如何判断一个前缀中`0`和`1`的个数是否一样多？

A：我们可以提前把这个字符串的前缀和求出来，如果这个前缀中`1`的个数刚好是这个前缀长度的**一半**，那么就可以

Q：如何判断 $a$ 经过若干次翻转前缀可否变成 $b$？

A：因为同一个前缀反转偶数次都相当于没动，反转奇数次相当于翻转1次。我们定义 $pre_i$ 表示 $[0,i]$ 这个前缀。显然，我们翻转 $pre_i,pre_j\ (i<j)$ 那么 $pre_i$ 是没有变化的，相当于被翻转0次。

所以，我们这样考虑：

我们令 $flg_i$ 表示当前 $pre_i$ 是否被翻转了（**结果意义上**）。比如现在 $pre_3,pre_1$ 各翻转1次，那么我们发现 $pre_1$ 是没有变化的，因此 $flg_1=\tt{false}$。我们可以发现 $flg_i$ 亦可以表示 $a_i$ 有没有被翻转（**结果意义上**）。

然后，我们**从后往前**枚举 $a_i,b_i$，如果此时 $a_i=b_i$ 并且 $flg_i=\tt{false}$，那么正好不用给它翻转，$a_i\not=b_i$ 并且 $flg_i=\tt{true}$ 时同样，不用我们给它做过多操作，这一位已经被翻转过来，满足我们的要求了。

但是，如果此时 $a_i=b_i$ 而且 $flg_i=\tt{true}$ 了，意味着本不用翻转，但现在你给它反转了，此时就要**翻回来**，$flg_i\Leftarrow\tt{false}$。**但是**，不要忘记，能够给 $pre_i$ 翻转的前提是 $pre_i$ 中`1`和`0`的个数一样多。所以，一旦不满足，我们就直接跳出循环大胆地输出`No`。

同理，如果 $a_i\not=b_i$ 并且 $flg_i=\tt{false}$ 了，意味着需要反转，但是此时你并没有给它翻转，此时就要**给它翻**，$flg_i\Leftarrow\tt{true}$，并且检查 $pre_i$ 是否满足翻的要求。

一直这么遍历，直到结束。输出`Yes`。

## 我的代码

```C++
#include<iostream>
#define N 300000
using namespace std;

int pa[N]; // 前缀和
int main() {
    string a, b; bool flg;
    int t, n; cin >> t;
    while (t--) {
        cin >> n >> a >> b, pa[0] = a[0] == '1', flg = false;
        for (int i=1; i<n; i++) // 求前缀和
            pa[i] = pa[i-1] + a[i] - '0';
        for (int i=n-1; i>=0; i--) { // 倒序遍历
            // 不用再翻转了
            if (a[i] - '0' ^ b[i] - '0' == flg) continue; // 直接走
            // 需要翻转，但是不满足条件
            if (pa[i] * 2 != i + 1) goto DIE; // 直接死
            // 没死，那么大胆翻转
            flg = !flg;
        }
        cout << "YES\n"; continue; // 没死，说明可行，输出完直接走
        DIE: cout << "NO\n"; // 竟然死了，不可行
    }
    return 0;
}
```

---

## 作者：Zzzzzzzm (赞：1)

# 题目难度：
略难的橙

# 题目分析：
我们总是只能更改$1$~$i$，且是把$0$变成$1$，$1$变成$0$。所以代表修改了前面的每一个点对于修改后面点没有任何帮助。即如果后面的无法修改且不全部为$0$，那么就肯定不行。

因此，我们从最后往前找，找到一个不等于0的就往前全部修改即可。输入时可以用前缀数组存，因为0变1不会变所以前缀数组有用的时候都是没有变化的，因为如果前面是奇数个肯定不行，如果为偶数个可以那么变化以后出现偶数个本质上没有变化。同时记录swap次数，加上swap即为是0或1。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int t;
int num[300005][2];
string a, b;
int lenth;
 
template<typename T>							//快读快写 
inline void read(T&x){
    x=0; char q; bool f=1;
    while(!isdigit(q = getchar()))  if(q == '-')    f = 0;
    while(isdigit(q)){
        x = (x<<1)+(x<<3)+(q^48);
        q = getchar();
    }
    x = f?x:-x;
}
 
template<typename T>
inline void write(T x){
    if(x<0){
        putchar('-');
        x = -x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
 
int main(){
	read(t);
	while(t--){									//t组数据 
		memset(num, 0, sizeof(num));
		read(lenth);							//读入 
		cin >> a >> b;
		a = ' ' + a;
		b = ' ' + b;
		for(register int i = 1; i <= lenth; ++i){	//初始化前缀数组 
			if(a[i] == '0'){
				num[i][0] = num[i-1][0] + 1;		//num[i][0]表示i个点的0的个数 
				num[i][1] = num[i-1][1];			//num[i][1]表示i个点的1的个数 
			}
			else{
				num[i][1] = num[i-1][1] + 1;
				num[i][0] = num[i-1][0];
			}
		}
		int Swap = 0;
		bool flag = false;
		for(register int i = lenth; i >= 1; --i){	//倒着搜 
			if(Swap % 2 == 0){						//如果为0		
				if(a[i] != b[i]){
					if(num[i][0] != num[i][1]){		//如果不等且换不了就不行 
						cout << "NO" << endl;
						flag = true;
						break;
					}
					Swap++;
				}
			}
			else{									//否则可以，交换当前点（虽然没用） 
				if(a[i] == '1')	a[i] = '0';
				else	a[i] = '1';
				if(a[i] != b[i]){
					if(num[i][0] != num[i][1]){
						cout << "NO" << endl;
						flag = true;
						break;
					}
					Swap++;
				}
			}
		}
		if(!flag)	cout << "YES" << endl;
	}
    return 0;
}
```


---

## 作者：Demoe (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1504B)

---

### $\text{Description}$

> 给定两个 $01$ 串 $\text{A}$，$\text{B}$，问通过操作是否可以将 $\text{A}$ 转换成 $\text{B}$。
>
> 每次操作可以选取 $\text{A}$ 的一个前缀，满足其中 $0$ 的个数和 $1$ 的个数相同，使得 $0$、$1$ 交换。

---

### $\text{Solution}$

考虑每次只能翻转**前缀**，那么即可从后往前对每一位进行操作。

每次操作一位时判断是否可行，然后拿个 $\text{tag}$ 记录一下操作奇偶性即可。

---

### $\text{Code}$

```cpp
// wish to get better qwq

#include<bits/stdc++.h>
#define re register int
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
#define dec(x) fixed<<setprecision(x)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

template<class T> inline void rd(T &x){
	int fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
template<class T> inline void wr(T x){
	if(x<0) x=-x,putchar('-');
	if(x<10){putchar(x+'0');return ;}
	int tmp[30]={0},cnt=0;
	while(x) tmp[cnt++]=x%10,x/=10;
	for(re i=cnt-1;i>=0;--i) putchar(tmp[i]+'0');
}

// ---------- IO ---------- //

const int N=3e5+5;
int t,n,s1[N],s2[N];
char a[N],b[N];

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(t);
	while(t--){
		rd(n);
		scanf("%s %s",a+1,b+1);
		for(re i=1;i<=n;++i) s1[i]=s1[i-1]+(a[i]=='1'),s2[i]=s2[i-1]+(b[i]=='1');
		int fl=1,tag=0;
		for(re i=n;i>0&&fl;--i){
			//cout<<i<<' '<<tag<<endl;
			if((a[i]^tag)==b[i]) continue;
			if((i&1)||s1[i]!=i/2){fl=0;break;}
			tag=1-tag;
		}
		puts(fl?"YES":"NO");
	}
	return 0;
}

// ---------- Main ---------- //

```

---

## 作者：vectorwyx (赞：1)

能够进行翻转操作的是 $a$ 的若干个前缀，假设这些前缀对应的区间（下标从 $1$ 开始 ）分别为 $[1,c_1],[1,c_2],\cdots,[1,c_k](c_1<c_2<\cdots<c_k)$，我们需要通过对这些区间进行翻转使 $a=b$。

首先，如果 $a[c_k+1,n]\not=b[c_k+1,n]$，答案一定为 `NO`。

否则，由于把一段区间翻转两次的效果相当于不翻转，所以先翻转 $[1,c_i]$ 再翻转 $[1,c_{i+1}]$ 的效果相当于只翻转区间 $[c_i+1,c_{i+1}]$。这意味着不管我们翻转了哪些前缀，最终的效果一定等价于对 $[1,c_1],[c_1+1,c_2],\cdots,[c_{k-1}+1,c_k]$ 中的某些区间进行翻转。反过来也是一样的，对 $[1,c_1],[c_1+1,c_2],\cdots,[c_{k-1}+1,c_k]$ 中的某些区间进行翻转的效果也一定等价于对某些前缀进行翻转。

故能通过翻转某些前缀使得 $a=b$ 当且仅当能通过翻转 $[1,c_1],[c_1+1,c_2],\cdots,[c_{k-1}+1,c_k]$ 中的某些区间使得 $a=b$，也就是说对于任意一段区间 $[l,r]=[c_i+1,c_{i+1}]$，有 $\forall j\in[l,r],a_j=b_j$ 成立或 $\forall j\in[l,r],a_j\not=b_j$ 成立。只要有一段区间不满足上述条件，答案即为 `NO`。否则答案为 `YES`。可以在求出这些区间后依次进行判断，时间复杂度为 $O(n)$

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=3e6+5;
bool a[N],b[N];
int rp[N][2];

void work(){
	int n=read();
	string s;cin>>s;
	fo(i,1,n) a[i]=(s[i-1]=='1');
	cin>>s;
	fo(i,1,n) b[i]=(s[i-1]=='1');
	int last=1;
	fo(i,1,n){
		rp[i][a[i]]=rp[i-1][a[i]]+1;
		rp[i][!a[i]]=rp[i-1][!a[i]];
		if(rp[i][0]==rp[i][1]){
			//printf("[%d %d]\n",last,i);
			bool f1=1,f2=1;
			fo(j,last,i) if(a[j]==b[j]) f1=0;
			fo(j,last,i) if(a[j]!=b[j]) f2=0;
			if(!(f1|f2)){
				puts("NO");
				return;
			}
			last=i+1;
		}
	}
	fo(i,last,n) if(a[i]!=b[i]){
		puts("NO");
		return;
	}
	puts("YES");
}

int main(){
	int T=read();
	while(T--) work(); 
	return 0;
}
```


---

## 作者：kradcigam (赞：1)

题目翻译：

给定两个 $n$ 位的 $01$ 序列 $a$ 和 $b$。

你可以对 $a$ 的任意一段含 $0$ 个数和含 $1$ 个数相同的前缀进行取反（即 $0$ 变 $1$，$1$ 变 $0$）

问是不是可以通过任意多的操作把 $a$ 变成 $b$。

考虑把 $a$ 分成尽量多的段，使得每一段的 $0$ 的个数和 $1$ 的个数都相同。当然最后还有剩余段。

对于 $0$ 的个数和 $1$ 的个数都相同的段，我们可以找到在 $b$ 中对应的段。如果这段和这段的取反都跟 $b$ 中对应的段不一样，答案就是 `NO`。

对于剩余段，如果它跟 $b$ 中的对应段不一样，答案也是 `NO`。

代码：
```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define mp make_pair
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){
	char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
void work(){
	int n=read();
	string a,b;
	cin>>a>>b;
	int s=0,x=0;
	F(i,0,SZ(a)){
		if(a[i]=='1')s++;
		else s--;
		if(!s){
			bool fa=true,fb=true;
			F(j,x,i){
				if(a[j]==b[j])fb=false;
				else fa=false;
			}
			if(!fa&&!fb){
				puts("NO");
				return;
			}
			x=i+1;
		}
	}
	F(i,x,SZ(a))
		if(a[i]!=b[i]){
			puts("NO");
			return;
		}
	puts("YES");
}
int main(){
	int _=read();while(_--)work();
	return 0;
}
```


---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1504B)

---

# 思路：

显然一个位置最多操作一次，由于本题只能操作前缀，因此从后往前判断，如果 $s_i$ 不等于 $t_i$，就要翻转一次，如果不能翻转则无解。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+10;
const int INF=0x3f3f3f3f;
int T,n;
char s[N],t[N];
signed main(){
    cin>>T;
    while(T--){
        cin>>n>>(s+1)>>(t+1);
        for(int i=1;i<=n;i++){
            s[i]-='0';
            t[i]-='0';
        }
        int cnt[2]={0},ok=1,f=0;
        for(int i=1;i<=n;i++){
            cnt[s[i]]++;
        }
        for(int i=n;i>=1;i--){
            s[i]^=f;
            if(s[i]!=t[i]){
                if(cnt[0]!=cnt[1]){
                    ok=0;
                    break;
                }else{
                    f^=1;
                }
            }
            cnt[t[i]]--;
        }
        if(ok){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
```

完结撒花~

---

## 作者：Norsuman371 (赞：0)

# 思路

首先，我们对 $a$ 进行翻转的条件是 $0$ 和 $1$ 的数量相同。储存次数的 $\textup{cnt}$，初始值为 $0$，当 $a_{i} = 1$ 时，$\textup{cnt} +1$，当 $a_{i} = 0$ 时，$\textup{cnt} - 1$。如果此时前缀的 $01$ 数量相等的话，那么 $\textup{cnt} = 0$ 否则 $\textup{cnt}$ 不为 $0$。后面 $a$ 到 $b$ 一直对前缀进行翻转，只要 $a$ 和 $b$ 不一样时，如果 $\textup{cnt} = 0$，就可以翻转 $a$，如果不为 $0$，就不可能翻转得到 $b$。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    string a, b;
    cin >> n >> a >> b;
    a.push_back('0');
    b.push_back('0');
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += (a[i] == '1') - (a[i] == '0'); 
        if ((a[i] == b[i]) != (a[i + 1] == b[i + 1]) && cnt != 0) { 
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int te;
    cin >> te;
    while (te--) {
        solve();
    }
}
```

# 记录

[AC](https://www.luogu.com.cn/record/163988407)

---

## 作者：Hooch (赞：0)

### 题目大意

给一个长度为 $n$ 的字符串 $a$。每次可以选择一段区间 $[1,i]$，将其里面的数进行翻转操作（$0$ 变 $1$，$1$ 变 $0$）。

给定一个长度同为 $n$ 的字符串 $b$，让你用翻转操作将 $a$ 转化为 $b$。输出 `YES` 或 `NO`。

### 思路

我们看样例解释，解释中有一步骤：先翻转 $[1,2]$ 这个原本就和 $b$ 的 $[1,2]$ 一样的区间，再翻转 $[1,12]$。

我们可以发现其中 $a$ 的 $[3,12]$ 与 $b$ 的 $[3,12]$ 完全不同。

于是就很好转换了，我们设一段连续的区间 $[i,j]$ 每个元素 $a_k$ 都与 $b_k$ 不同。

设 $f_i=1$ 表示 $[1,i]$ 能被翻转，反之 $f_i=0$ 就不能。

于是这个区间想要与 $b$ 相同，则 $f_{i-1}=1$ 且 $f_{j}=1$。

### 代码

注释在代码里。

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (register int i(j); i <= n; ++i)
#define rep2(i, j, n) for (register int i(j); i >= n; --i)
#define il inline
using namespace std;
const int N = 3e5 + 5, inf = 0x3f3f3f3f;

template <typename T>
il void read(T &x) {
   x = 0; T f = 1; char ch = getchar();
   while (!isdigit(ch)) f -= (ch == '-') << 1, ch = getchar();
   while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar(); x *= f;
}
template <typename T>
il void write(T x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int cnt1, cnt2, t, n; string a, b; bool f[N];
main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n;
		cin >> a >> b; cnt1 = cnt2 = 0; memset(f, 0, sizeof f);
		rep1(i, 0, n - 1) {
			if (a[i] == '1') ++cnt2; else ++cnt1; //统计 1 和 0 的数量 
			if (cnt2 == cnt1) f[i] = 1; //处理 f 数组 
		} bool flg = 1;
		for (int i = 0; i < n; ) {
			if (a[i] ^ b[i]) {
				if (i != 0 && !f[i - 1]) {flg = 0; break;}
				int j = i;
				for (; j < n && a[j] ^ b[j]; ++j) ;// 找到这段区间的右端点 
				--j;
				if (!f[j]) {flg = 0; break;}
				i = j + 1; 
			} else ++i;
		}
		cout << (flg ? "YES" : "NO") << endl;
	}
}
```

---

## 作者：LiveZoom (赞：0)

# CF1504B 题解

赛时调了半天没调出来，赛后又调了半天还发帖询问后才过的。。。

## 题意

给定两个 $01$ 串 $a,b$，定义操作规则：

对于一个 $01$ 串，每次只能选择串中从 $1\sim i$ 的数字进行翻转（$0$变$1$，$1$变$0$），而且这 $i$ 个数字 $0$ 的个数与 $1$ 的个数是相同的。

问你能否对 $a$ 操作后变成 $b$。

## 思路

这题我是从后往前考虑的。

结论：从后往前扫，如果碰到 $a_i=b_i$ 且 $a_{i-1} \neq b_{i-1}$ 则就必须将 $1\sim i-1$ 翻转。易知此时 $1\sim i-1$ 中 $0$ 的个数不等于 $1$ 的个数则输出$\texttt{NO}$。如果坚持到底的话，就输出$\texttt{YES}$。

感性理解：找到从右到左满足 $a_i=b_i$ 并且 $a_{i-1} \neq b_{i-1}$ 的第一个 $i$，任意取一数 $j(i<j\leq n)$。那么我们将 $1\sim j-1$ 翻转后，此时 $i\sim j-1$ 就不满足了，所以还要再翻转一次，就跟只翻转 $1\sim i - 1$ 一样了。

## 实现

很明显我们每一次对 $1\sim i-1$ 进行翻转操作时，不能直接模拟，否则时间卡爆你。那么怎么优化呢？

考虑到这是一个 $01$ 串，所以翻转结果只跟翻转次数有关，而且这里的操作是对一个连续的区间考虑的，所以完全可以用树状数组来写（类似于[树状数组 2](https://www.luogu.com.cn/problem/P3368)），然后正常写就可以了。

Tip：多组数据时，树状数组清空不能用 ```memset```，否则会 T。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int T, n;
int s[N];

string a1, b1;
int a[N], b[N];

int sum[N << 2];
int lowbit (int x) {
	return x & (-x);
}

void update (int x, int y) {//树状数组
	while (x <= n) {
		sum[x] += y;
		x += lowbit(x);
	}
	return ;
}

int query (int x) {
	int res = 0;
	while (x != 0) {
		res += sum[x];
		x -= lowbit(x);
	}
	return res;
}

int main() {
	cin >> T;
	while (T--) {
		cin >> n >> a1 >> b1;
		s[0] = 0;
		for (int i = 1; i <= n; ++i) a[i] = a1[i - 1] - '0', b[i] = b1[i - 1] - '0', s[i] = s[i - 1] + a[i];//求前缀1的个数
		for (int i = 1; i <= n; ++i) sum[i] = 0;
		bool flag = true;
		for (int i = n; i >= 1; --i) {
			int k = query(i);
			if (k % 2 == 1) {
				a[i] ^= 1;
			}
			if (a[i] == b[i]) continue ;
			if (s[i] != i - s[i]) { flag = false; break ; }//如果不能进行翻转，就退出
			update(1, 1), update(i, -1);//对1~i-1 全部加上1
			s[i - 1] = i - 1 - s[i - 1];//前缀1变化
		}
		puts(flag == true ? "YES" : "NO");
	}
	return 0;
}
```

时间复杂度：$O(n\log n)$

能过。

$\text{Upd on 2021.4.10}$

这种思路可以 $O(n)$ 写，而且 $n\log n$ 的写法貌似复杂了（

定义一个计数器 $k$ 当这个时候需要翻转时就将 $k+1$，那么每次遍历到时，$k$ 就是次数。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int T, n;
int s[N];

string a1, b1;
int a[N], b[N];

int main() {
	cin >> T;
	while (T--) {
		cin >> n >> a1 >> b1;
		s[0] = 0;
		for (int i = 1; i <= n; ++i) a[i] = a1[i - 1] - '0', b[i] = b1[i - 1] - '0', s[i] = s[i - 1] + a[i];
		bool flag = true; int k = 0;
		for (int i = n; i >= 1; --i) {
			if (k % 2 == 1) {
				a[i] ^= 1;
			}
			if (a[i] == b[i]) continue ;
			if (s[i] != i - s[i]) { flag = false; break ; }
			++k;
			s[i - 1] = i - 1 - s[i - 1];
		}
		puts(flag == true ? "YES" : "NO");
	}
	return 0;
}
```

---

