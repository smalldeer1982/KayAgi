# Suitable Replacement

## 题目描述

You are given two strings $ s $ and $ t $ consisting of small Latin letters, string $ s $ can also contain '?' characters.

Suitability of string $ s $ is calculated by following metric:

Any two letters can be swapped positions, these operations can be performed arbitrary number of times over any pair of positions. Among all resulting strings $ s $ , you choose the one with the largest number of non-intersecting occurrences of string $ t $ . Suitability is this number of occurrences.

You should replace all '?' characters with small Latin letters in such a way that the suitability of string $ s $ is maximal.

## 说明/提示

In the first example string "baab" can be transformed to "abab" with swaps, this one has suitability of 2. That means that string "baab" also has suitability of 2.

In the second example maximal suitability you can achieve is 1 and there are several dozens of such strings, "azbz" is just one of them.

In the third example there are no '?' characters and the suitability of the string is 0.

## 样例 #1

### 输入

```
?aa?
ab
```

### 输出

```
baab
```

## 样例 #2

### 输入

```
??b?
za
```

### 输出

```
azbz
```

## 样例 #3

### 输入

```
abcd
abacaba
```

### 输出

```
abcd
```

# 题解

## 作者：RE_Prince (赞：2)

# CF825D Suitable Replacement

[link](https://www.luogu.com.cn/problem/CF825D)

## Sol

思路：二分，构造。

我们每次统计在 $s$ 中每个字符有多少，$t$ 也是同理。这样就能计算出还需要每个字符多少个才能满足在 $s$ 中有 $x$ 个 $t$。当所需字符超出问号的个数时，就可以证明 $x$ 这么多次不能成立，要缩小。否则增大。

那么这样就求出了 $t$ 最多可以出现多少次，构造也就很简单了。每遇到一个问号时，遍历所有 $26$ 个字母，看哪个字母现在还需要输出。输出完后，这个字母对应的所需数量减少。如果没有要输出的字母，直接输出任意一个字母就好了。

有一个小优化：当二分时，可以让 $r=\left\lceil \frac{10^6}{|t|}\right\rceil$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k,ans,cnt;
string s,t;
unordered_map<char,int> mp,p2;
bool check(int x)
{
	int ret=cnt;
	for(char i='a';i<='z';i++)
	{
		if(p2[i]-mp[i]*x<0) ret-=(mp[i]*x-p2[i]);//说明这个字符不够
		if(ret<0) return 0;
	}
	return 1;
}
signed main()
{
	cin>>s>>t;
	int l1=s.size(),l2=t.size();
	for(i=0;i<l2;i++) mp[t[i]]++;
	for(i=0;i<l1;i++) cnt+=(s[i]=='?'),p2[s[i]]++;//统计问号个数和字符个数
	int l=0,r=ceil(1e6/l2);
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	for(char i='a';i<='z';i++) mp[i]*=ans;//现在每个字母所需的个数
	for(i=0;i<l1;i++)//构造
	{
		if(s[i]=='?')
		{
			for(char j='a';j<='z';j++)
				if(p2[j]-mp[j]<0)//如果还需要这个字母
				{
					mp[j]--;
					cout<<j;//输出，需求--
					goto end;
				}
			cout<<"a";
			end:;
		}
		else cout<<s[i];
	}
    return 0;
}
```

---

## 作者：_liuyi_ (赞：1)

# 思路
我们用 $num_i$ 和 $pos_i$ 分别表示 $i$ 这个字符在 $S$ 和 $T$ 中出现的次数，然后我们可以考虑二分填完后最多有多少个子串 $T$，用 $cnt$ 表示问号出现次数，那么二分判断条件显然为 $\sum_{i=0}^{25}$ $\max(pos_i \times mid-num_i,0)\le cnt$，二分出次数后直接填就可以了，具体看代码实现，~~记得开long long~~。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
#define ti (db)((db)clock() / CLOCKS_PER_SEC)
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
typedef unsigned long long ull;
typedef double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
constexpr int N=1e6+10;
constexpr int mod=1e9+7;
//constexpr int mod=998244353;
string a,b;
ll num[N],cnt,pos[N];
inline bool check(int x){
    ll tmp=cnt;
    rep(i,0,25) tmp-=max(1ll*pos[i]*x-num[i],0ll);
    return tmp>=0;
}
inline void solve(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin >> a >> b;
    rep(i,0,SZ(a)-1){
        if(a[i]!='?') num[a[i]-'a']++;                 
        else cnt++; 
    }
    rep(i,0,SZ(b)-1) pos[b[i]-'a']++;
    int l=-1,r=SZ(a)+1;
    while(l+1<r){
        int mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    rep(i,0,25) pos[i]=max(pos[i]*l-num[i],0ll);
    // rep(i,0,25) printf("%d ",pos[i]);
    rep(i,0,SZ(a)-1){
        if(a[i]!='?') cout << a[i];
        else{
            bool ok=false;
            rep(j,0,25) 
                if(pos[j]){
                    cout<<(char)(j+'a');
                    pos[j]--;
                    ok=true;
                    break;
                }  
            if(!ok) cout<<(char)'a';
        }
    }
}
int main(){
    int T=1;
    //scanf("%d",&T);
    while(T--) solve();
}
```


---

## 作者：luo_shen (赞：1)

## 题意描述
给定一个带有不定字符 $?$ 的字符串 $s$，和一个匹配串 $t$，可以将 $?$ 替换为任何字符。要求给出一种替换方案，使得在所有替换方案中，将字符串 $s$ 进行一定的排列后，该方案得到的**不相交子串** $t$ 数量最多。
## 题目分析
这道题目肯定是要贪心考虑，在所有的替换方案中，最后字符串 $s$ 中含有的字符比例越接近字符串 $t$ 中含有的字符比例，得到的子串 $t$ 的数量越多。

分别统计 $s,t$ 中含有的字符的出现次数 $nums,numt$。对于每次填完后，$s$ 中子串 $t$ 出现的次数最多为：令字符 $c$ 为出现在 $t$ 中的字符中，$\frac{nums_c}{numt_c}$ 最小的字符，此时只需将 $?$ 改为字符 $c$ 即可。
## Code
```cpp
string s,t;
int numt[26],nums[26];//如前文所示，nums表示字符在s中出现次数，numt表示字符在t中出现次数
signed main(){
    cin>>s;
    cin>>t;
    for(int i=0;i<t.size();i++){//先统计字符在t中出现次数
        numt[t[i]-'a']++;
    }
    for(int i=0;i<s.size();i++){//统计非?字符在s中出现次数
        if(s[i]=='?'){
            continue;
        }
        nums[s[i]-'a']++;
    }
    for(int i=0;i<s.size();i++){//依次修改每个?字符
        if(s[i]!='?'){
            continue;
        }
        int mn=1e9,num=0;
        for(int j=0;j<26;j++){
            if(mn*numt[j]>nums[j]){
            //因为为了防止出现除0的情况，将除法变为乘法，这样就不会出现修改numt[j]为0的字符
                num=j;
                mn=nums[j]/numt[j];
            }
        }//寻找nums[j]：numt[j]最小的字符
        s[i]=num+'a';
        nums[num]++;
    }
    cout<<s<<endl;
    return 0;
}
```
## 扩展
若将题目中不相交的字符串 $t$ 改为可以相交的字符串 $t$，该怎么办呢？

令 $t'$ 为字符串 $t$ 进行 `kmp` 匹配后的 `border` ，$T$ 为 $t$ 尾部去掉 $t;$ 后的字符串，那么 $s$ 排列后的字符串 $s'$ 必然为 $T+T+...+T+t'+other$。所以可以先做一遍 `kmp`，求出 $t'$，先填满一个 $t'$，随后在 $t'$ 从 $t$ 中去掉，将新字符串作为上文的 $t$，贪心跑即可。

---

## 作者：_ayaka_ (赞：0)

### 思路
由于 $s$ 可以随意进行排列，那么只要在 $s$ 中每有一组与 $t$ 中的字符相同的字符，那就可以认为是有一个子串 $t$。基于此，这里给出一个极其简单的方法。

首先读入 $s$ 与 $t$ 并统计 $s$ 中非 $?$ 的字符的数量 $num$。

接下来进行循环替换。步骤如下：

1. 定义 $cnt$ 为在字符串 $t$ 中替换到的位置。
1. 循环替换 $s$ 中的 $?$ 为 $t_{cnt}$。
1. 在进行替换前进行判定：若 $num_{t_{cnt}}$ 仍有值，那就使 $cnt+1$ 并再进行一次判定。

（没看懂可以配合代码食用）

这样我们就可以实现在 $s$ 中有尽可能多的 $t$ 了。时间复杂度最好 $O(n)$，最坏 $O(n^2)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s,t;
int n,m,k,num[30],sum[30],cnt;
signed main() {
	cin>>s>>t;
	n=s.length();
	m=t.length();
//	cout<<n<<" "<<m<<"\n";
	for(int i=0;i<n;i++){
		if(s[i]!='?') num[s[i]-'a'+1]++;
	}
	for(int i=0;i<n;i++){
		if(s[i]=='?'){
			cnt=(cnt+1)%m;
			while(num[t[cnt]-'a'+1]){
				num[t[cnt]-'a'+1]--;
				cnt=(cnt+1)%m;
			}
			s[i]=t[cnt];
		}
	}
	cout<<s;
	return 0;
}
```

---

