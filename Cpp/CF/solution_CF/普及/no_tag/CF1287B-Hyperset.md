# Hyperset

## 题目描述

Bees Alice and Alesya gave beekeeper Polina famous card game "Set" as a Christmas present. The deck consists of cards that vary in four features across three options for each kind of feature: number of shapes, shape, shading, and color. In this game, some combinations of three cards are said to make up a set. For every feature — color, number, shape, and shading — the three cards must display that feature as either all the same, or pairwise different. The picture below shows how sets look.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1287B/2d643729d5939800827cb912354d70a177513bf3.png)

Polina came up with a new game called "Hyperset". In her game, there are $ n $ cards with $ k $ features, each feature has three possible values: "S", "E", or "T". The original "Set" game can be viewed as "Hyperset" with $ k = 4 $ .

Similarly to the original game, three cards form a set, if all features are the same for all cards or are pairwise different. The goal of the game is to compute the number of ways to choose three cards that form a set.

Unfortunately, winter holidays have come to an end, and it's time for Polina to go to school. Help Polina find the number of sets among the cards lying on the table.

## 说明/提示

In the third example test, these two triples of cards are sets:

1. "SETT", "TEST", "EEET"
2. "TEST", "ESTE", "STES"

## 样例 #1

### 输入

```
3 3
SET
ETS
TSE```

### 输出

```
1```

## 样例 #2

### 输入

```
3 4
SETE
ETSE
TSES```

### 输出

```
0```

## 样例 #3

### 输入

```
5 4
SETT
TEST
EEET
ESTE
STES```

### 输出

```
2```

# 题解

## 作者：yuzhechuan (赞：5)

代码实现其实很简单，并不需要什么三进制啊离散啊之类的

---

### 题解：

我们枚举其中的两个串$i$和$j$，这样就可以得到合法的第三个串，且一定是唯一的

为了不重复计算，我们可以只统计$i$之前或$j$之后有几个要求的串

为了减小代码量和常数，我们可以选择前者

用一个map记录成为过$i$的串分别出现过几次，他们是可以被计算进答案的

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=1005;
int n,m;
string s[N];
long long ans;
map<string,int> mp;

signed main(){
	read(n);read(m);
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			string aim=""; //目标串
			for(int k=0;k<m;k++){
				if(s[i][k]==s[j][k]) aim+=s[i][k]; //相同的添加方案
				else{
					if(s[i][k]!='S'&&s[j][k]!='S') aim+='S'; //不同的添加方案
					if(s[i][k]!='E'&&s[j][k]!='E') aim+='E';
					if(s[i][k]!='T'&&s[j][k]!='T') aim+='T';
				}
			}
			ans+=mp[aim]; //看看曾出现过几次
		}
		mp[s[i]]++; //它也变成“曾出现过”
	}
	write(ans);
}
```

---

## 作者：ix35 (赞：2)

## CF 1297 B：Hyperset

很多人用 map 存储卡的信息，时间复杂度是 $O(n^2k+n^2\log n)$，我觉得这样很不优雅，所有我采用了 Trie 来实现查找（实际效率应该是差不多的，但这样常数可能小一些），时间复杂度是 $O(n^2k)$。

基本思路很简单，枚举两张卡，那么对于每个属性我们就可以求出第三卡的对应属性（如果前两张卡的 $i$ 属性相同，第三张卡也要是这个属性；否则第三张卡就应该是不同于前两张卡的那种属性），建立高度为 $k$ 的三叉 Trie 存储卡牌信息，在 Trie 上实现第三张牌的计数。

注意最后答案要除以 $3$，容易发现每个情况都数了 $3$ 次。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1510,MAXK=40;
int n,k,tot=1,a[MAXN][MAXK],ch[MAXN*MAXK*3][3],ed[MAXN*MAXK*3];
char c[MAXK];
ll ans;
int main () {
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) {
		scanf("%s",c+1);
		int cur=1;
		for (int j=1;j<=k;j++) {
			a[i][j]=(c[j]=='S'?0:(c[j]=='E'?1:2));
			if (!ch[cur][a[i][j]]) {ch[cur][a[i][j]]=++tot;}
			cur=ch[cur][a[i][j]];
		}
		ed[cur]++;
	}
	for (int i=1;i<=n;i++) {
		for (int j=i+1;j<=n;j++) {
			int cur=1;
			for (int l=1;l<=k;l++) {
				cur=ch[cur][a[i][l]==a[j][l]?a[i][l]:3-a[i][l]-a[j][l]];
			}
			ans+=ed[cur];
		}
	}
	printf("%lld\n",ans/3);
	return 0;
}
```


---

## 作者：liuyz11 (赞：1)

# 题解 CF1287B 【Hyperset】

题目大意：有n张卡，每张卡有k个特征，每个特征有三种（'S', 'E', 'T'），让你选出三张卡组成一套，使得三张卡中的每个特征全部相等或者全部不同。如样例三中的"SETT", "TEST", "EEET"是一套，"TEST", "ESTE", "STES"也是一套，问一共能选出几套。

这题数据很小，n在1500以内，把所有状态直接改为三进制数也是在longlong范围内，怎么做都行。

我的解法极其繁杂，转成数字后离散化再进行计数。

先枚举两张卡i和j，这样可以直接求出第三张卡的状态（如果前两张相同，第三张也相同，如果前两张不同，第三张就是剩下的那种），答案加上符合该种状态卡的个数。

又臭又长的代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 1505
#define MAXM 35
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

map<ll, int> Rank;
char st[MAXM];
int a[MAXN][MAXM], c[MAXN], sum[MAXN];
ll num[MAXN], b[MAXN];

int judge(char ch){
	if(ch == 'S') return 0;
	if(ch == 'E') return 1;
	if(ch == 'T') return 2;
}

int main(){
	int n, len;
	scanf("%d%d", &n, &len);
	rep(i, 1, n){
		scanf("%s", st);
		rep(j, 0, len - 1){
			num[i] = num[i] * 3 + judge(st[j]);
			a[i][j + 1] = judge(st[j]);
		}
		b[i] = num[i];
	}
	sort(b + 1, b + n + 1);
	rep(i, 1, n) Rank[b[i]] = i;
	rep(i, 1, n) c[i] = Rank[num[i]];
	int ans = 0;
	rep(i, 1, n){
		rep(j, i + 1, n){
			ll s = 0;
			rep(k, 1, len){
				int x = (6 - a[i][k] - a[j][k]) % 3;
				s = s * 3 + x;	
			}
			if(Rank.find(s) != Rank.end()) ans += sum[Rank[s]];
		}
		sum[c[i]]++;
	}
	printf("%d\n", ans);
    return 0;
}
```

---

## 作者：_weishiqi66_ (赞：0)

# 思路
要从所有卡牌中选三个使其满足，每个特征全部相等或全部不同。最直接的思路是枚举三个卡牌并逐伟判断是否满足条件。时间复杂度为 $O(n^3 \cdot k)$。

优化时我们考虑有什么是多余的枚举。我们发现卡牌的特征只有三种——"S"，"T"，"E"且我们选取的卡牌也只有三种。这说明，当三种卡牌第 $i$ 位的特征不同时，则在这三张卡牌的第 $i$ 位必然包括"S"，"T"，"E"三种特征。所以我们完全可以通过枚举两个卡牌就可以推出第三个满足条件卡牌的特征。并判定第三个卡牌是否存在，存在则对答案有贡献。

# 题解

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int rd() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while(ch<='9'&&ch>='0') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
int n,m;
string c[1600];
unordered_map<string,int>f;
signed main(){   
  /// freopen("in.txt","r",stdin);
    n=rd(); m=rd();
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=n;i++) f[c[i]]++;
    int ans=0;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i==j) continue;
            c[0]="";
            for(int k=0;k<m;k++) {
                if(c[i][k]==c[j][k]) c[0]+=c[i][k];
                else {
                    if(c[i][k]!='S'&&c[j][k]!='S') c[0]+='S';
                    if(c[i][k]!='E'&&c[j][k]!='E') c[0]+='E';
                    if(c[i][k]!='T'&&c[j][k]!='T') c[0]+='T';
                } 
            }
            ans+=f[c[0]];    
            

        }
    }
  //答案需要除6的原因是因为在枚举的过程中会进行重复计算。ABC、BAC、CAB本质上是一样的。
  //在计算答案时只需要记录一次即可。
  //重复的计算的次数为三个数的排列组合个数

    cout<<ans/6<<'\n';
    return 0;
}
```

---

## 作者：Maysoul (赞：0)

模拟赛 T1 出了这道题，是谁暴力都写挂了我不说。

于是有了这篇题解。

## 简化题意：

给定 $n$ 个长度相同的字符串，对于三个字符串中相同位置的三个字符，要么三个全都相等，要么全部不等，都满足条件的能组成一套，问能组成几套。

## 简述思路：

直观的思路是，枚举三个元素进行挨个字符比较，这样的做法是 $O(n^{3}k)$ 的，无法通过本题。

仔细想想，我们其实只需要枚举两个元素就可以了，因为一定存在一个字符串，能和前两个元素组成一套，证明如下：

如果相同位置的两个字符不相等，那么必然存在一个和这两个字符不同的字符。

如果两个字符相等，那么只需令当前位置的字符也和这两个字符相等。

那么我们构造出这个字符串之后，只需在之前输入的字符串里查找即可。

因为有多个相同的字符被统计，所以我们需要对其进行去重。

去重也很简单，对于一个已经被统计的三元组 $ (i,j,k) $，用 `map` 标记即可。

## CODE：

```cpp
//2023/8/5
//别着急，先通读一遍题目
//别忘了开long long
//写完先看一遍怎么降复杂度
//要么开全局变量要么给定初值
//想想看，有什么情况需要特判
//看看数组开的够不够大
//std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num,ans;
string a[2020];
string s="";
void check(char x,char y)
{
	if(x=='S'){
		if(y=='T') s+='E';
		if(y=='E') s+='T';
	}
	if(x=='E'){
		if(y=='S') s+='T';
		if(y=='T') s+='S';
	}
	if(x=='T'){
		if(y=='S') s+='E';
		if(y=='E') s+='S';
	}
}
map<string,int> mp;
map<set<int>,int> mg;
int main()
{
	int n,k;
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]=i;
	}
	for (int i=1;i<=n;i++){
		for (int j=i+1;j<=n;j++){
			for (int p=0;p<k;p++){
				//cout<<a[i][p]<<" "<<a[j][p]<<endl;
				if(a[i][p]==a[j][p]) s+=a[i][p];
				else check(a[i][p],a[j][p]);
			}
			//cout<<s<<endl;
			int a[3]={i,j,mp[s]};
			set<int> se(a,a+3);//这里可以用tuple来减小常数
			if(mp[s]&&!mg[se]){
				ans++;
				mg[se]=1;
			}
 			s="";
		}
	}
	cout<<ans<<endl;
	return 0;
	
}
```




---

## 作者：gyh20 (赞：0)

枚举加map维护

枚举前两个位置，求出一个可以与这两个位置构成合法的集合的字符串，用map查找是否存在即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0,f=1;
	re char v=getchar();
	while(v<'0'||v>'9'){
		if(v=='-')f=-1;
	v=getchar();}
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t*f;
}
int n,k,ans;
char s[2002][32],t[32];
map <string,int> mp;
int main(){
n=read();
k=read();
for(re int i=1;i<=n;++i)scanf("%s",s[i]),mp[s[i]]=1;
 
for(re int i=1;i<=n;++i){
	for(re int j=i+1;j<=n;++j){
		for(re int kk=0;kk<k;++kk){
			if(s[i][kk]!=s[j][kk]){
				t[kk]='S'+'E'+'T'-s[i][kk]-s[j][kk];
			}
			else t[kk]=s[i][kk];
		}
		if(mp[t])++ans;
	}
}
printf("%d",ans/3);
}
```


---

