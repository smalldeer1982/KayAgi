# Mishkin Energizer

## 题目描述

为了准备与老朋友 Fernan 的决斗，Edmond 正在制作一种名为 "Mishkin Energizer" 的能量饮料。该饮料由一个长度为 $n$ 的字符串 $s$ 构成，仅包含字符 L、I 和 T，分别对应饮料中三种不同物质的含量。

当饮料中所有三种物质的数量相等时，我们称其为平衡的。为了增强气场并确保决斗胜利，Edmond 必须通过以下操作使初始字符串变为平衡状态：

1. 选择一个下标 $i$ 满足 $s_i \neq s_{i+1}$（此时 $i + 1$ 必须不超过字符串当前长度）。
2. 在它们之间插入一个字符 $x$（可以是 L、I 或 T），且满足 $x \neq s_i$ 和 $x \neq s_{i+1}$。

帮助 Edmond 通过不超过 $\textbf{2n}$ 次操作使饮料平衡并赢得决斗。若存在多种解，可输出任意一种。若不可能实现，需报告此情况。

## 说明/提示

第一个测试案例中，可执行以下操作序列：TILII $\rightarrow$ TLILII $\rightarrow$ TLTILII $\rightarrow$ TLTLILII $\rightarrow$ TLTLTILII。

第二个测试案例中无法进行任何操作，答案为 $-1$。

第三个测试案例中初始字符串已满足三种物质数量相等。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
5
TILII
1
L
3
LIT```

### 输出

```
4
1
2
3
4
-1
0```

# 题解

## 作者：SUNCHAOYI (赞：6)

不难发现形如 `LIT` 的串是万能的。证明如下：

- 可以多生成一个 `L` 变为 `LILT`。
- 可以多生成一个 `T` 变为 `LTIT`。
- 想要多生成一个 `I`，先选择上面两个的其中一个操作，然后同理即可。

进一步地，只要存在相邻两个字母不同，就可以花费一个操作变为万能串。每一步最多操作两次即可向着目标前进，故总次数不会超过 $2n$。

由于还需要记录路径，当 `LIT` 变为 `ILT` 后，需要注意万能串最左侧的位置会增加 $1$。直接用 `while` 配套着 `swap` 需求的写法最为简洁。

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 105;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,tot,ok,cnt[200];char s[MAX];
vector <int> ans;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	tot = 'L' ^ 'I' ^ 'T';
	t = read ();
	while (t--)
	{
		n = read ();scanf ("%s",s + 1);
		ok = cnt['L'] = cnt['I'] = cnt['T'] = 0;
		ans.clear ();
		for (int i = 1;i <= n;++i)
		{
			if (i > 1 && s[i] != s[i - 1]) ok = 1;
			++cnt[s[i]];
		}
		if (!ok) {puts ("-1");continue;} //无法构造出万能串，肯定是无解
		if (cnt['L'] == cnt['I'] && cnt['I'] == cnt['T']) {puts ("0");continue;}//无需操作就直接特判
		for (int i = 2;i <= n;++i)
		{
			if (s[i] == s[i - 1]) continue;
//由 AB -> ACB 构造万能串
			int x = s[i - 1],z = s[i],y = tot ^ (x ^ z),p = i - 1;
			ans.push_back (p);++cnt[y];
			while (cnt[x] != cnt[y] || cnt[x] != cnt[z] || cnt[y] != cnt[z])
			{
				if (cnt[x] > cnt[z]) ans.push_back (p),++cnt[z],swap (y,z);
				else ans.push_back (++p),++cnt[x],swap (x,y);//万能串最左侧的位置右移
			}
			break;	
		}
		printf ("%d\n",ans.size ());
		for (auto v : ans) printf ("%d\n",v);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：qinyiyang2012 (赞：2)

### 思路分析

很显然的贪心。

假定我们现在处理到了第 $i$ 个字符，其中 $1 \le i < |s|$ 且 $s_i \ne s_{i+1}$。
1. 若要插入的字符数量小于另外两个字符数量的话，则插入这个字符一定是不劣的，故直接插入即可。
2. 还有一种情况，就是当前可插入的字符的数量都不比其他两个字符的数量小，此时我们选择插入满足插入后字符数量与最小字符数量的差值最小的字符。
3. 若每个位置都不可插入或操作次数大于了 $2n$，则无解。

### 代码

接下来就是一些实现细节了。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e2+5;//注意最多可能操作2n次，不要开小
int T,n,ans[N];
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n>>s;
		int cnt=0,L=0,I=0,T=0;//cnt为操作次数，L,I,T 分别记录 L,I,T 的数量
		bool ok=false;//记录是否成功
		while(1){
			L=0,I=0,T=0;
			for(int i=0;i<s.size();i++){
				L+=(s[i]=='L');
				I+=(s[i]=='I');
				T+=(s[i]=='T');
			}//统计一下到目前为止L,I,T的个数
			if(L==I&&I==T){//若数量相等，直接跳出
				ok=true;
				cout<<cnt<<"\n";
				break;
			}
			cnt++;
			if(cnt>n*2)break;//若操作次数大于2n，跳出
			bool flag=false;//记录是否插入成功
      //第一种情况
			for(int i=0;i<s.size()-1;i++){
				if(s[i]==s[i+1])continue;
				if(s[i]!='L'&&s[i+1]!='L'){
					if(L<max({L,I,T})){
						ans[cnt]=i;//记录插入位置
						s=s.substr(0,i+1)+'L'+s.substr(i+1);//拼接
						flag=true;
						break;
					}
				}
				if(s[i]!='I'&&s[i+1]!='I'){
					if(I<max({L,I,T})){
						ans[cnt]=i;//记录插入位置
						s=s.substr(0,i+1)+'I'+s.substr(i+1);//拼接
						flag=true;
						break;
					}
				}
				if(s[i]!='T'&&s[i+1]!='T'){
					if(T<max({L,I,T})){
						ans[cnt]=i;//记录插入位置
						s=s.substr(0,i+1)+'T'+s.substr(i+1);//拼接
						flag=true;
						break;
					}
				}
			}
			if(flag)continue;
      //第二种情况
			int minn=INT_MAX,id=-1;
			char ch;
			for(int i=0;i<s.size()-1;i++){
				if(s[i]==s[i+1])continue;
				if(s[i]!='L'&&s[i+1]!='L'){
					if(L-max({L,I,T})<minn){
						minn=L-max({L,I,T});
						ch='L';
						id=i;
					}
				}
				if(s[i]!='I'&&s[i+1]!='I'){
					if(I-max({L,I,T})<minn){
						minn=I-max({L,I,T});
						ch='I';
						id=i;
					}
				}
				if(s[i]!='T'&&s[i+1]!='T'){
					if(T-max({L,I,T})<minn){
						minn=T-max({L,I,T});
						ch='T';
						id=i;
					}
				}
			}
			if(id==-1){//若插入失败，则无解
				ok=false;
				break;
			}
			ans[cnt]=id;//记录插入位置
			s=s.substr(0,id+1)+ch+s.substr(id+1);//拼接
		}
		if(!ok)cout<<"-1\n";//若无解则输出-1
		else{
			for(int i=1;i<=cnt;i++){
				cout<<ans[i]+1<<"\n";//由于地址从0开始，故输出需要加一
			}
		}
	}
	return 0;
}
```

---

## 作者：potata111 (赞：1)

## [_CF2092D_](https://www.luogu.com.cn/problem/CF2092D) Mishkin Energizer

### 解析

显然在注意到 $n$ 的数据范围时，  
我们就可以考虑本题的**大模拟**解法了。

首先，对于每个选定的操作数 $i$，添加的 $x$ 是固定的，即：
$$
x = L\ \operatorname{xor}\ I\ \operatorname{xor}\ T\ \operatorname{xor}\ S_i\ \operatorname{xor}\ S_{i + 1}
$$

这仅是一个计算方法，其正确性我们不难证明。

---

**证明**：

$$
∵\ x \neq S_i;\ x \neq S_{i + 1};\ x \in \{\texttt{L},\ \texttt{I},\ \texttt{T}\}
$$
$$
∴\ x \in \{\texttt{L},\ \texttt{I},\ \texttt{T}\}\ - \{S_i,\ S_{i + 1}\}
$$

又因为 $S_i \neq S_{i + 1}$ 且 $S \in \{\texttt{L},\ \texttt{I},\ \texttt{T}\}$。

故 $\{\{\texttt{L},\ \texttt{I},\ \texttt{T}\}\ - \{S_i,\ S_{i + 1}\}\}$ 中有且仅有 $1$ 个元素。

证得：$x$ 的取值是唯一的，且显而易见地可以通过上式计算出来。

---

于是对于每次操作（最坏情况下）：

我们使用 $O(n)$ 的时间复杂度**遍历**字符串。

$O(1)$ **决策**每个字符，并在 $S_i$ 与 $S_{i + 1}$ 对应的 $x$ 较少时选择添加，否则决策下一个。

每次**添加**的时间复杂度为 $O(n)$。

共 $2n$ 次操作。故时间复杂度为 $O(n^3)$。


---


### 代码

码风清奇、注释详尽。

```cpp
#include<iostream>
#include<vector>
#include<string>
#include<map>

#define potata 105
#define cal ('L' ^ 'I' ^ 'T')
using namespace std;

int q;
string str;
int n;
map<char, int> cnt;
vector<int> ans;

bool equal() 
{ 
    return (cnt['L'] == cnt['I'] && cnt['L'] == cnt['T'] && cnt['I'] == cnt['T']);
} // 判断饮料平衡

void solve() 
{
    cin >> n;
    cin >> str;

    cnt.clear();
    ans.clear();
    // 多测不清见祖宗

    for (int i = 0; i < n; i++)
        cnt[str[i]]++;
    
    int step = 0;
    while (equal() == false && step <= 2 * n) // O(2n) 次操作
    {
        bool flg = false;

        for (int i = 0; i < str.size() - 1; i++) // O(n) 遍历
        {
            if (str[i] == str[i + 1]) 
                continue; // 可行性

            char ch = cal ^ str[i] ^ str[i + 1];
            int Cnt = cnt[ch];
            int Max = max(cnt['L'], max(cnt['I'], cnt['T']));
            // 最优性

            if (Cnt < Max)
            {
                str.insert(str.begin() + i + 1, ch); // O(n) 插入
                ans.push_back(i + 1);

                cnt[ch]++;
                flg = true;
                break;
            } // 小优化
        }

        if (flg == false) 
        {
            for (int i = 0; i < str.size() - 1; i++) 
            {
                if (str[i] != str[i + 1]) 
                {
                    char ch = cal ^ str[i] ^ str[i + 1];

                    str.insert(str.begin() + i + 1, ch);
                    ans.push_back(i + 1);

                    cnt[ch]++;
                    flg = true;
                    break;
                }
            }
        } // 确保最优性

        if (flg == false) 
            break; // 可行性（剪枝）
        
        step++;
    } // 上面的步骤是至多 2n 次操作的最优方案

    if (equal()) 
    {
        int Ans = ans.size();
        
        cout << Ans << '\n';
        for (int i = 0; i < Ans; i++)
            cout << ans[i] << '\n';
    }

    else
        cout << -1 << '\n';
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie();

    cin >> q;

    while (q--)
        solve();
    
    return 0;
}
```

---

## 作者：znzryb (赞：1)

我写的算法相当于是一个贪心，就是先看可不可以插入出现次数最少的字符，然后看能不能插入次小的，再看能不能插入次次小的。

不断重复这个贪心操作，如果发现次数超过了 $2N$ 次还是无法达到平衡要求，那么直接输出 $-1$ ，反之如果中间哪次平衡了，那么就输出步骤数量以及保存好的步骤。

```
// Problem: D. Mishkin Energizer
// Contest: Codeforces - Codeforces Round 1014 (Div. 2)
// URL: https://codeforces.com/contest/2092/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// by znzryb
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define fi first
#define se second
#define pb push_back
#define SZ(a) ((int) a.size())

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<ll,ll> pll;
typedef array<ll,3> arr;
typedef double DB;
typedef pair<DB,DB> pdd;
typedef pair<ll,bool> plb;
constexpr ll MAXN=static_cast<ll>(1e2)+10,INF=static_cast<ll>(5e18)+3;

ll N,M,T;
// char S[MAXN];
ll cnt[28];
char ingre[4]={'L','I','T'};

inline bool cmp(const char &a,const char &b){
	return cnt[a-'A']<cnt[b-'A'];
}

// LIT
inline void solve(){
	cin>>N;
	vector<char> s;
	for(int i=0;i<=26;++i){
		cnt[i]=0;
	}
	FOR(i,1,N){
		char a;
		cin>>a;
		s.pb(a);
		++cnt[a-'A'];
		// cin>>S[i];
	}
	// vector<ll> pos;
	bool canOper=false;
	for(int i=0;i<(int)s.size()-1;++i){
		if(s[i]!=s[i+1]){
			canOper=true;
		}
	}
	if(!canOper){
		cout<<-1<<"\n";
		return;
	}
	// 这道题目应该是O(n^2)的
	bool haveAns=false;
	vector<ll> ans;
	for(int i=1;i<=2*N+1;++i){
		if(cnt['L'-'A']==cnt['I'-'A'] && cnt['L'-'A']==cnt['T'-'A']){
			haveAns=true;
			break;
		}
		bool hasOp=false;
		sort(ingre,ingre+3,cmp);
		for(int i=0;i<3;++i){
			char obj=ingre[i];
			for(int i=0;i<(int)s.size()-1;++i){
				if(s[i]!=s[i+1]){
					if(s[i]!=obj && s[i+1]!=obj){
						s.insert(s.begin()+i+1,obj);
						ans.pb(i);
						++cnt[obj-'A'];
						hasOp=true;
					}
					if(hasOp){
						break;
					}
				}
				
			}
			if(hasOp){
				break;
			}
		}
		
	}
#ifdef LOCAL
    for(int i=0;i<s.size();++i){
    	cerr<<s[i];
    }
    cerr<<"\n";
    cerr<<"T:"<<cnt['T'-'A']<<"\n";
    cerr<<"I:"<<cnt['I'-'A']<<"\n";
    cerr<<"L:"<<cnt['L'-'A']<<"\n";
#endif
	if(haveAns){
		cout<<ans.size()<<'\n';
		for(int i=0;i<ans.size();++i){
			cout<<ans[i]+1<<"\n";
		}
	}else{
		cout<<-1<<"\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
	// solve();
	return 0;
}
/*
AC
https://codeforces.com/contest/2092/submission/315587701
*/
```

---

