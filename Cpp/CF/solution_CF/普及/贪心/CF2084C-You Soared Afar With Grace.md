# You Soared Afar With Grace

## 题目描述

给定两个长度为 $n$ 的排列 $a$ 和 $b$ $^{\text{∗}}$。你最多可以进行 $n$ 次如下操作：

- 选择两个下标 $i$ 和 $j$（$1 \le i, j \le n$，$i \ne j$），交换 $a_i$ 和 $a_j$，同时交换 $b_i$ 和 $b_j$。

判断是否可以通过这些操作使得 $a$ 和 $b$ 互为逆序排列。换句话说，对于每个 $i = 1, 2, \ldots, n$，满足 $a_i = b_{n + 1 - i}$。

如果可能，输出任意一个有效的操作序列；否则输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

## 说明/提示

- 在第二个测试用例中，$b$ 已经是 $a$ 的逆序排列，因此不需要操作。  
- 在第三个测试用例中，执行以下操作后，$b$ 将成为 $a$ 的逆序排列：  
  - 交换 $a_1, a_2$ 和 $b_1, b_2$。此时 $a = [3, 1, 2, 4]$，$b = [4, 2, 1, 3]$。  
- 在第四个测试用例中，按顺序执行以下操作后，$b$ 将成为 $a$ 的逆序排列：  
  - 交换 $a_1, a_2$ 和 $b_1, b_2$。此时 $a = [5, 2, 1, 3, 4]$，$b = [5, 3, 4, 2, 1]$。  
  - 交换 $a_1, a_3$ 和 $b_1, b_3$。此时 $a = [1, 2, 5, 3, 4]$，$b = [4, 3, 5, 2, 1]$。  

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2
1 2
1 2
2
1 2
2 1
4
1 3 2 4
2 4 1 3
5
2 5 1 3 4
3 5 4 2 1
5
3 1 2 4 5
1 2 3 4 5```

### 输出

```
-1
0
1
1 2
2
1 2
1 3
-1```

# 题解

## 作者：Eason_cyx (赞：1)

由题目条件可以得到其实对于所有 $i$，$a_i$ 和 $b_i$ 都是捆绑在一起的。那么对于所有 $(a_i,b_i)=(x,y)$，至多有一组 $(x,y)$ 使得不存在一组 $(y,x)$。

如果存在这样的 $(x,y)$，就应当先将其换到 $i=\lceil\dfrac{n}{2}\rceil$ 的位置；然后，对于所有 $1 \le i \le \lfloor\dfrac{n}{2}\rfloor$，应当找到这个 $(x,y)$ 对应的 $(y,x)$ 的位置，然后将这一组换到 $n-i+1$ 的位置。这样就可以在大约 $\dfrac{n}{2}$ 次操作内完成，可以通过。时间复杂度 $O(n\log n)$。

**注意：题目严格要求不能 $i=j$，所以进行操作时，务必注意两个位置是否不相同。**

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005], b[200005];
map<pair<int, int>, int> mp;
map<pair<int, int>, int> pos;
pair<int, int> ans[800005];
int main() {
    int t; cin >> t;
    while(t--) { mp.clear(); pos.clear();
        int n; cin >> n;
        for(int i = 1;i <= n;i++) cin >> a[i];
        for(int i = 1;i <= n;i++) cin >> b[i];
        for(int i = 1;i <= n;i++) mp[{a[i], b[i]}]++;
        int cnt = 0; for(int i = 1;i <= n;i++) {
            if(!mp[{a[i], b[i]}]) continue;
            mp[{a[i], b[i]}]--; 
            if(!mp[{b[i], a[i]}]) cnt++;
            else mp[{b[i], a[i]}]--;
        } if(cnt > 1) { cout << "-1\n"; continue; }
        if(cnt == 0) { int anscur = 0;
            for(int i = 1;i <= n;i++) pos[{a[i], b[i]}] = i;
            for(int i = 1;i <= n/2;i++) {
                int now = pos[{b[i], a[i]}], to = n - pos[{a[i], b[i]}] + 1;
                if(now != to) {
                    ans[++anscur] = {now, to};
                    int s = pos[{b[i], a[i]}];
                    swap(a[s], a[to]); swap(b[s], b[to]);
                    pos[{b[i], a[i]}] = to; pos[{a[s], b[s]}] = now;
                }
            } cout << anscur << "\n"; if(anscur > n) while(1);
            for(int i = 1;i <= anscur;i++) {
                cout << ans[i].first << " " << ans[i].second << endl;
            }
        } else { int anscur = 0; mp.clear();
            for(int i = 1;i <= n;i++) pos[{a[i], b[i]}] = i;
            for(int i = 1;i <= n;i++) mp[{a[i], b[i]}]++;
            int p = 1; while(p <= n) {
                if(a[p] != b[p] && pos[{b[p], a[p]}] == 0) break;
                if(a[p] == b[p] && mp[{a[p], b[p]}] == 1) break;
                p++;
            } if(p != ((n+1) / 2)) {
                ans[++anscur] = {p, (n+1) / 2};
                swap(a[p], a[(n+1) / 2]); swap(b[p], b[(n+1) / 2]);
                pos[{a[(n+1) / 2], b[(n+1) / 2]}] = (n+1) / 2; pos[{a[p], b[p]}] = p;
            } for(int i = 1;i <= n/2;i++) {
                int now = pos[{b[i], a[i]}], to = n - pos[{a[i], b[i]}] + 1;
                if(now != to) {
                    ans[++anscur] = {now, to};
                    int s = pos[{b[i], a[i]}];
                    swap(a[s], a[to]); swap(b[s], b[to]);
                    pos[{b[i], a[i]}] = to; pos[{a[s], b[s]}] = now;
                }
            } cout << anscur << "\n"; if(anscur > n) while(1);
            for(int i = 1;i <= anscur;i++) {
                cout << ans[i].first << " " << ans[i].second << endl;
            }
        }
    } return 0;
}
```

---

## 作者：AK_400 (赞：0)

注意到相同下标的两个数一定不会分开。

于是如果 $\forall i\in[1,n],\exist j\in[1,n],a_i=b_j,a_j=b_i$，并且 $a_i=b_i$ 的出现次数为 $n\bmod 2$ 才有解。

令 $c_{a_i}=i$，只需要把 $c_{b_i}$ 换到 $n-i+1$ 就好了。

复杂度：$O(n)$。

code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int n,a[200005],b[200005],c[200005];
vector<pair<int,int>>ans;
void slv(){
    ans.clear();
    read(n);
    for(int i=1;i<=n;i++)read(a[i]),c[a[i]]=i;
    for(int i=1;i<=n;i++)read(b[i]);
    int cnt=0;
    for(int i=1;i<=n;i++){
        cnt+=(a[i]==b[i]);
    }
    if(cnt!=(n&1)){
        cout<<-1<<endl;
        return;
    }
    for(int i=1;i<=n;i++){
        if(b[c[b[i]]]!=a[i]){
            cout<<-1<<endl;
            return;
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i]==b[i]&&(i!=(n+1>>1))){
            ans.push_back({i,n+1>>1});
            swap(a[i],a[n+1>>1]);
            swap(b[i],b[n+1>>1]);
            swap(c[a[i]],c[a[n+1>>1]]);
            break;
        }
    }
    for(int i=1;i<=(n>>1);i++){
        if(c[b[i]]==n-i+1)continue;
        ans.push_back({c[b[i]],n-i+1});
        swap(a[c[b[i]]],a[n-i+1]);
        swap(b[c[b[i]]],b[n-i+1]);
        swap(c[a[n-i+1]],c[a[c[b[i]]]]);
    }
    cout<<ans.size()<<endl;
    for(auto x:ans)cout<<x.first<<" "<<x.second<<endl;
    return;
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{59}$ 篇题解。

# $\mathbf{0x01}$ 承

给定两个数组 $a,b$，判断能否同时交换 $a_i,a_j$ 和 $b_i,b_j$ 最多 $n$ 次，使得一个数组是另一个数组的倒序。

# $\mathbf{0x02}$ 转

考虑使用 $\text{map}$ 记录每个 $(a_i,b_i)$，每次交换就相当于交换 $(a_i,b_i)$ 和 $(a_j,b_j)$，「一个数组是另一个数组的倒序 」也就是对于任意 $(a_i,b_i)$ 都满足 $(b_i,a_i)=(a_{n-i+1},b_{n-i+1})$。

于是可以遍历每一个 $(a_i,b_i)$，如果 $(b_i,a_i)$ 不再本来应该在的位置就把它移动到这个位置，同时记录答案。

那么如何判断无解呢？可以发现，如果对于一个 $(a_i,b_i)$ 满足 $a_i=b_i$，且这样的数对数量大于 $1$，就意味着不能通过移动使其满足条件，无解。

此外，如果 $n$ 为奇数且只存在一组如上的 $(a_i,b_i)$，则可以把它移动到中间（即 $\frac{n+1}{2}$ 的位置上），仍能满足条件。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n;
vector<ll>a,b;
vector<pair<ll,ll>>ans;
map<pair<ll,ll>,ll>mp;
void SWAP(ll x,ll y){
	ans.push_back({x,y});
	swap(a[x],a[y]),swap(b[x],b[y]);
	mp[{a[x],b[x]}]=x,mp[{a[y],b[y]}]=y;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		a.resize(n+1),b.resize(n+1),ans.clear(),mp.clear();
		for(ll i=1;i<=n;i++)cin>>a[i];
		for(ll i=1;i<=n;i++)cin>>b[i];
		for(ll i=1;i<=n;i++){
			mp[{a[i],b[i]}]=i;
		}
		ll cnt=0,wz=0;
		for(ll i=1;i<=n;i++){
			if(a[i]==b[i]||!mp[{b[i],a[i]}])cnt++,wz=i;
		}
		if(cnt>1){
			cout<<"-1\n";
			continue;
		}
		if(cnt>0&&wz!=(n+1)/2)SWAP(wz,(n+1)/2);
		for(ll i=1;i<=n/2;i++){
			if(ll p=mp[{b[i],a[i]}];p!=n-i+1){
				SWAP(p,n-i+1);
			}
		}
		cout<<ans.size()<<endl;
		for(auto [x,y]:ans){
			cout<<x<<" "<<y<<endl; 
		}
	}
}
```

---

## 作者：hongshixiaobai (赞：0)

# CF2084C You Soared Afar With Grace 题解
[传送门](https://www.luogu.com.cn/problem/CF2084C)
## 思路
因为 $a,b$ 两个数组同时交换，所以每个 $a_i$ 对应的 $b_i$ 不会变化，设 $ind_i$ 表示 $\sum_{j = 1}^{j\le n} [a_j = i]j$，其中 $[\ \ ]$ 为艾弗森括号。所以当且仅当 $\forall i,a_i=b_{ind_{b_{i}}}$ 时才存在可能的交换方式。

考虑如何统计，首先若 $n$ 为奇数，显然此时应有一位 $a_i = b_i$，首先将其交换到第 $\lceil\frac{n}{2}\rceil$ 位，然后对于所有 $i<\lceil\frac{n}{2}\rceil$，将与其对应的 $a_j$ 交换到第 $n-i+1$ 位即可
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,i,ind[200005],cnte,inde,flag;
struct _
{
	long long a,b;
}p[200005];
vector<_>ans;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--)
	{
		flag = 0;
		cnte = 0;
		cin>>n;
		ans.clear();
		for(i = 1;i<=n;i++)cin>>p[i].a;
		for(i = 1;i<=n;i++)cin>>p[i].b;
		for(i = 1;i<=n;i++)if(p[i].a == p[i].b)inde = i,cnte++;
		if(cnte!=(n&1))
		{
			cout<<"-1\n";
			continue;
		}
		if(cnte&&inde!=n/2+1)
            ans.push_back({inde,n/2+1}),swap(p[inde],p[n/2+1]);
		for(i = 1;i<=n;i++)ind[p[i].a] = i;
		for(i = 1;i<=n;i++)
		{
			if(p[ind[p[i].b]].b!=p[i].a)
			{
				flag = 1;
				break;
			}
		}
		if(flag)
		{
			cout<<"-1\n";
			continue;
		}
		for(i = 1;i<=n;i++)
		{
			if(ind[p[i].b]!=n-i+1)
			{
				ans.push_back({ind[p[i].b],n-i+1});
				swap(p[ind[p[i].b]],p[n-i+1]);
				ind[p[ind[p[i].b]].a] = ind[p[i].b];
				ind[p[i].b] = n-i+1;
			}
		}
		cout<<ans.size()<<'\n';
		for(i = 0;i<ans.size();i++)
			cout<<ans[i].a<<' '<<ans[i].b<<'\n';
	}
}
```

---

