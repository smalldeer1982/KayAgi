# Task On The Board

## 题目描述

Polycarp wrote on the board a string $ s $ containing only lowercase Latin letters ('a'-'z'). This string is known for you and given in the input.

After that, he erased some letters from the string $ s $ , and he rewrote the remaining letters in any order. As a result, he got some new string $ t $ . You have to find it with some additional information.

Suppose that the string $ t $ has length $ m $ and the characters are numbered from left to right from $ 1 $ to $ m $ . You are given a sequence of $ m $ integers: $ b_1, b_2, \ldots, b_m $ , where $ b_i $ is the sum of the distances $ |i-j| $ from the index $ i $ to all such indices $ j $ that $ t_j > t_i $ (consider that 'a'&lt;'b'&lt;...&lt;'z'). In other words, to calculate $ b_i $ , Polycarp finds all such indices $ j $ that the index $ j $ contains a letter that is later in the alphabet than $ t_i $ and sums all the values $ |i-j| $ .

For example, if $ t $ = "abzb", then:

- since $ t_1 $ ='a', all other indices contain letters which are later in the alphabet, that is: $ b_1=|1-2|+|1-3|+|1-4|=1+2+3=6 $ ;
- since $ t_2 $ ='b', only the index $ j=3 $ contains the letter, which is later in the alphabet, that is: $ b_2=|2-3|=1 $ ;
- since $ t_3 $ ='z', then there are no indexes $ j $ such that $ t_j>t_i $ , thus $ b_3=0 $ ;
- since $ t_4 $ ='b', only the index $ j=3 $ contains the letter, which is later in the alphabet, that is: $ b_4=|4-3|=1 $ .

Thus, if $ t $ = "abzb", then $ b=[6,1,0,1] $ .

Given the string $ s $ and the array $ b $ , find any possible string $ t $ for which the following two requirements are fulfilled simultaneously:

- $ t $ is obtained from $ s $ by erasing some letters (possibly zero) and then writing the rest in any order;
- the array, constructed from the string $ t $ according to the rules above, equals to the array $ b $ specified in the input data.

## 说明/提示

In the first test case, such strings $ t $ are suitable: "aac', "aab".

In the second test case, such trings $ t $ are suitable: "a", "b", "c".

In the third test case, only the string $ t $ equals to "aba" is suitable, but the character 'b' can be from the second or third position.

## 样例 #1

### 输入

```
4
abac
3
2 1 0
abc
1
0
abba
3
1 0 1
ecoosdcefr
10
38 13 24 14 11 5 3 24 17 0```

### 输出

```
aac
b
aba
codeforces```

# 题解

## 作者：Eibon (赞：5)

因为字符串一定合法，不难发现，如果当前字符在序列中最大，则该位 $b[i]$ 一定为零。

考虑模拟，设 $ans[i]$ 表示当前 $i$ 所对应的字符。

先将每个字符的出现次数 $num[i]$ 处理出来，用 $a[i]$ 记录出现的所有字符并进行排序。

再将所有不为零的 $b[j]$ 减去与 $i$ 的距离绝对值。

循环直到所有位为零即可。

记得处理 $b[i]$ 均为零的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=50+5;
int T,n,m,cnt,VIP,v;
int a[maxn],b[maxn],num[maxn],ans[maxn];
char s[maxn];
bool check()
{
	for(int k=1;k<=m;k++){
		if(b[k]){
			return 1;
		}
	}
	return 0;
}
signed main()
{
	scanf("%lld",&T);
	while(T--){
		cnt=VIP=0;
		memset(ans,0,sizeof ans);
		memset(num,0,sizeof num);
		scanf("%s%lld",s+1,&m);
		n=strlen(s+1);
		for(int i=1;i<=n;i++){
			num[s[i]-'a'+1]++;
			if(num[s[i]-'a'+1]==1){
				a[++cnt]=s[i]-'a'+1;
			}
		}
		sort(a+1,a+cnt+1);
//		for(int i=1;i<=26;i++){
//			cout<<num[i]<<" ";
//		}cout<<endl;
		for(int i=1;i<=m;i++){
			scanf("%lld",&b[i]);
		}
		while(check()){
			VIP++;v=0;//cout<<1;
			for(int i=1;i<=m;i++){
				if(!b[i]&&!ans[i]){
					v++;
				}
			}
			while(1){
				if(num[a[cnt-VIP+1]]<v){
					//cout<<cnt-VIP+1<<" "<<v<<endl;
					VIP++;
				}
				else{
					break;
				}
			}//cout<<VIP<<endl;
			for(int i=1;i<=m;i++){
				if(!b[i]&&!ans[i]){
					ans[i]=a[cnt-VIP+1];
					//cout<<ans[i]<<endl;
				}
			}
			for(int i=1;i<=m;i++){
				if(ans[i]==a[cnt-VIP+1]){
					for(int j=1;j<=m;j++){
						if(b[j]){
							b[j]-=abs(i-j);
						}
					}
				}
			}
		}
		VIP++;v=0;
		for(int i=1;i<=m;i++){
			if(!b[i]&&!ans[i]){
				v++;
			}
		}
		while(1){
			if(num[a[cnt-VIP+1]]<v){
				VIP++;
			}
			else{
				break;
			}
		}
		for(int i=1;i<=m;i++){
			if(!b[i]&&!ans[i]){
				ans[i]=a[cnt-VIP+1];
			}
		}
		for(int i=1;i<=m;i++){
			char c=(char)ans[i]+'a'-1;
			cout<<c;
		}
		printf("\n");
	}
	return 0;
}
//dyyyyds
/*
1
codeforces
10
38 13 24 14 11 5 3 24 17 0
*/
```

---

## 作者：pocafup (赞：4)

这题赛时不知道为啥脑抽就是想不出，赛后直接秒了(

首先，由于题目说了一定有解，我们考虑什么情况能够确定答案。

可以发现，当某个点的数字为0时，填当前最大的字母一定可行。

现在问题来了，其他的数字怎么办呢？

可以发现，这题的 string length 很小。所以我们可以每次更新某一个字母的时候，就将其他所有的字母减去相应的贡献。

例：

```
ccabdf
6 2 1 0
答案为 ????
```
假设先填 $l$，那么我们可以更新答案最后一位为 $l$，之后对每个位置相应的更新。

```
ccabdf
6-3 2-2 1-1 0
答案为 ???f
```

可以发现第二三个位置变为 $0$ 了，于是我们找到第一个有重复超过两次的字母，将它填入。

```
ccabdf
3-3 0 0 0
答案为 ?ccf
```
例子随意造的，~~凑出ccf纯属巧合~~

于是下一步我们就把最后一个 $0$ 更新完，然后输出答案就好了。

代码：

```
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <unordered_map>
#include <cstring>
using namespace std;
unordered_map<char,int> mp;
int t,n,pos[55];
char ans[55];
queue<int> q2,q;
bool vis[55];
string s;
signed main(){
  cin >> t;
  while(t--){
    cin >> s >> n;
    unordered_map<char,int> tmp;
    memset(vis,0,sizeof(vis));
    swap(tmp,mp);//O(1)清空，用 mp.clear()是O(n)的（虽然好像没啥大用）
    for (int i : s) mp[i-96]++;//存每个字符出现的次数
    for (int i=0;i<n;i++) {
      cin >> pos[i];
      if (pos[i]==0) q2.push(i),vis[i] = true;//如果等于0就进队
    }
    swap(q,q2);
    int curr = 26;
    while(mp[curr]<q.size()) curr--;
    while(!q.empty()){
      int qf = q.front(); q.pop();
      for (int i=0;i<n;i++) {
        if (vis[i]) continue;
        pos[i]-=abs(qf-i);
        if (pos[i]==0) q2.push(i),vis[i] = true;//更新所有旁边的数字
      }
      ans[qf] = curr;
      if (q.empty()) {
        swap(q,q2);
        curr--;
        while(mp[curr]<q.size() && curr!=0) curr--;
        //如果某个字母更新完了，看看他有没有下一个字母可以继续更新，下一个字母可能更新的东西已经全部扔进q2了，现在只需要一个swap就能轻松搞定
      }
    }
    for (int i=0;i<n;i++) cout << char(ans[i]+96);//输出答案
    cout << endl;
  }
}
```

---

## 作者：Eazin_star (赞：2)

### 思路
首先理解题意后我们会发现，每组数字里面一定会有 $0$，因为一个字符串里面一定会有至少一个最大的字符。所以这道题！就解决了！

那我们来重新梳理一遍思路，首先找到数组中有多少个 $0$ ，然后找到 $0$ 所对应的字符，然后减去目前确定的字符所带来的距离。这样一次操作的完成了，不断重复操作，直到所有位置全部确定。

可能单说有点抽象，我们来看代码。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, m;
queue <int> q, qq; //记录有多少个0的位置
map<char, int> mp; //记录每个字符出现的次数
int a[55];
char ans[55]; //记录答案
bool vis[55]; //记录这个位置是否确定
string s;

int main() {
	scanf("%d", &t);
	while (t--) {
		cin >> s;
		scanf("%d", &m);
		memset(vis, 0, sizeof vis); //记得初始化
		mp.clear();
		for (int i = 0; i < s.size(); i++) { //统计字符数量
			char c = s[i];
			mp[c]++;
		}
		for (int i = 1; i <= m; i++) { //统计一开始有多少个0
			scanf("%d", &a[i]);
			if (!a[i]) qq.push(i), vis[i] = 1;
		}
		swap(q, qq);
		char cur = 'z'; // 记录当前已确定的字符中最小的字符
		while (mp[cur] < q.size()) cur--; //确定字符
		while (!q.empty()) {
			int t = q.front();
			q.pop();
			for (int i = 1; i <= m; i++) {
				if (vis[i]) continue; //如果字符已经确定，跳过
				a[i] -= abs(t-i); //减去距离
				if (!a[i]) qq.push(i), vis[i] = 1; //如果为0，加入队列
			}
			ans[t] = cur; //记录答案
			if (q.empty()) {
				swap(q, qq);
				cur--;
				while (mp[cur] < q.size() && cur != 'a') cur--; //找到目前为0的合法字符
			}
		}
		for (int i = 1; i <= m; i++) cout << ans[i]; //输出答案
		putchar('\n');
	}	
	return 0; //完结撒花！！！
}
```


---

## 作者：EuphoricStar (赞：1)

## 思路

考虑按字母顺序从大到小填。

设当前正在填的字母为 $c$，那么现在答案中已经填入的字母一定比当前正在填的字母字典序小。暴力计算与他们的下标差，如果与 $b_i$ 相等，就说明 $c$ 可以填在 $i$。

注意如果合法位置的个数大于原串中 $c$ 出现的次数，就要把 $c$ 往前移。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 55;

int n, m, a[maxn], cnt[30];
char s[maxn], t[maxn];

void solve() {
	memset(t, 0, sizeof(t));
	memset(cnt, 0, sizeof(cnt));
	scanf("%s%d", s + 1, &m);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) {
		++cnt[s[i] - 'a'];
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &a[i]);
	}
	for (char ch = 'z'; ch >= 'a'; --ch) {
		vector<int> v;
		for (int i = 1; i <= m; ++i) {
			if (!t[i]) {
				int sum = 0;
				for (int j = 1; j <= m; ++j) {
					if (t[j]) {
						sum += abs(i - j);
					}
				}
				if (sum == a[i]) {
					v.pb(i);
				}
			}
		}
		while (cnt[ch - 'a'] < (int)v.size()) {
			--ch;
		}
		for (int i = 0; i < (int)v.size(); ++i) {
			t[v[i]] = ch;
		}
	}
	printf("%s\n", t + 1);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：F_Mu (赞：1)

**题意**

给一个字符串$t$，和一个长度为$m$的数组$b[]$，要求构造一个字符串$s$，$s$中的字符都出现在$t$中，对于$s[i]$而言，对于任意$j$，如果有$s[i]<s[j]$，则$\sum abs(i-j)=b[i]$，即$i$到所有比$s[i]$大的下标距离之和等于$b[i]$

**分析**

字符串$t$提供的就是每个字符的数量，我们发现对于字符最大的位置，$b[i]$肯定为$0$，然后次大的位置，$b[i]$被这些最大的位置影响，以此类推，我们保存一个已经填进去的数组，然后每一次枚举的时候将这个位置与数组中的数求绝对值之和，因为已经填进去的字符肯定比当前位置字符要大，所以如果这个和等于$b[i]$，则这个数这一轮是可以填的，然后就是从大到小枚举字符，如果字符数比当前填的个数大，则选择，否则选小的字符

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
 
#include <bits/stdc++.h>
 
#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int maxn = (ll) 3e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int T = 1;
char s[maxn];
int a[maxn];
int num[maxn];
char ans[maxn];
bool vis[maxn];
 
void solve() {
    int n;
    cin >> (s + 1) >> n;
    rep(i, 1, n)cin >> a[i], vis[i] = false;
    rep(i, 0, 26)num[i] = 0;
    rep(i, 1, strlen(s + 1))++num[s[i] - 'a'];
    vector<int> v;
    int m = n;
    int now = 25;
    while (m > 0) {
        int tot = 0;
        vector<int> pos;
        rep(i, 1, n) {
            if (vis[i])
                continue;
            int sum = 0;
            for (auto &to:v)
                sum += abs(to - i);
            if (sum == a[i])
                pos.push_back(i);
        }
        for (auto &to:pos) {
            vis[to] = true;
            ++tot;
            v.push_back(to);
        }
        while (num[now] < tot)
            --now;
        m -= tot;
        for (auto &to:pos)
            ans[to] = (char) (now + 'a');
        --now;
    }
    rep(i, 1, n)cout << ans[i];
    cout << '\n';
}
 
signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```



---

## 作者：Lily_White (赞：0)

~~我不看数据范围把 $n$ 当作 $2\times 10^5$ 导致卡了好久~~。

构造题。

注意到，如果一个位置的 $b$ 值为 $0$，那这个位置的字母一定是最大的。推而广之，当没有构造完成时，我们考虑所有当前 $b$ 值为 $0$ 的位置（记它们构成集合 $S$），从大到小考虑各个字母，如果这个字母的出现次数大于 $|S|$，就全部填上这个字母。接着，对于  $\forall i \in S$，考虑所有满足 $b_j \neq 0$ 的 $j$，让$b_j=b_j - |i -j|$即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
  ios::sync_with_stdio(false);
  int tc;
  cin >> tc;
  while (tc--) {
    string s;
    cin >> s;
    int n = s.length();
    int m;
    cin >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    map<char, int> cnt;
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    auto it = cnt.rbegin();
    string ans(m, '#');
    while (true) {
      vector<int> cur;
      for (int i = 0; i < m; i++)
        if (a[i] == 0) cur.push_back(i);
      if (cur.empty()) break;
      while (it->second < cur.size()) it++;
      for (int y : cur) ans[y] = it->first;
      it++;
      for (int i = 0; i < m; i++)
        if (a[i] != 0)
          for (int y : cur) a[i] -= abs(i - y);
        else
          a[i] = 0x3f3f3f3f;
    }
    cout << ans << endl;
  }
  return 0;
}
```

---

