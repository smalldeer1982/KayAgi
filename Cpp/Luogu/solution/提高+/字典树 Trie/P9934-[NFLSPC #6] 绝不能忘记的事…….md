# [NFLSPC #6] 绝不能忘记的事……

## 题目背景

> 那件事…… 绝对不能忘记！

## 题目描述

你在电脑内记录了一条绝对不能忘记的事。但是，因为 1064 病毒的入侵，它被电脑忘记了。更可怕的是，1064 病毒似乎拥有某种跨物种传播的能力，导致你也忘记了这件事。

万幸，在 1064 病毒让你和你的电脑忘记这件事之前，你及时将这件事的记录复制了 $n$ 份。但是，由于你和你的电脑在执行这件艰巨的任务的过程中受到 1064 病毒的影响忘记了很多可以忘记的事，所以你进行的操作有点奇怪。

- 首先，这件事的记录是一个长度未知（因为你已经忘记了它的长度）的字符串，称作 **记录串**。对于一份复制，你将记录串切成了三段非空的字符串 **片段**。**不同复制的场合，切割的方案不一定相同**。你暂且将这三份 **片段** 依次称作 **前面**，**中间** 和 **后面**。
- 因为电脑忘记了很多可以忘记的事，所以某些复制中的某些片段可能被忘记了。具体而言，前面有可能被替换为 `QIANMIANWANGLE`，中间有可能被替换为 `ZHONGJIANWANGLE`，后面有可能被替换为 `HOUMIANWANGLE`；在发生替换的场合，表示电脑 **完全忘记** 了这一段片段；否则，表示电脑 **完全记得** 该片段。
- 你终于想起了一件绝不能忘记的事：那就是那绝不能忘记的记录串中，**恰出现了一次** `NFLSPC#6QIDONG` 作为连续子串。除此之外，记录串中的所有其它字符都是 **小写英文字符**。并且，因为你和你的电脑始终记得这件事有多么重要，所以你在划分的时候，无意中让某一个片段恰好为 `NFLSPC#6QIDONG`；你的电脑也在每一份记录中忠实地记得这一段片段。
- 于是，你的电脑最终还记得的东西，就是：$n$ 份复制，每份复制由三段非空字符串构成，依次表示这份复制的三份片段；其中恰有一段为 `NFLSPC#6QIDONG`，另外两段要么是一串仅由小写英文字母构成的非空串，要么是对应的前面/中间/后面忘了。
- 邪恶的 1064 病毒不肯罢休，它篡改了你电脑中的信息，使得你的 $n$ 份复制不一定是自洽的。

你确信 1064 病毒没有能力篡改过多的信息，并且它绝对敌不过你和你的电脑对彼此牢牢记住的 `NFLSPC#6QIDONG` 的信念。因此，你的复制仍然满足上文中所述的性质（恰有一段是 `NFLSPC#6QIDONG`，另外两段要么忘了要么是小写字母非空串）。

你的目标是，寻找到初始的那绝不能忘记的记录串。这个记录串需要满足的条件是，恰出现一次 `NFLSPC#6QIDONG`，其余字符均是小写英文字符，且其匹配尽量多的复制串。

- 记录串与复制串匹配的要求是，记录串存在一种划分，使得三段划分与复制串的三段分别相同，或者复制串中这段划分忘了（此时本段划分中，记录串为任何非空英文字符串均合法）。

你希望求出该记录串能匹配的最多复制串数目。至于记录串本身，你更希望将它深深地埋藏于心底，因此你不需要求出它。

> 那忘记的事只会使你的心灵更加轻盈 / 那未曾忘记的事则会让你的心灵更加坚硬 /

## 说明/提示

对于所有数据，保证输入的所有字符串长度之和不超过 $10 ^ 6$。

- 子任务 1（$20$ 分）：保证复制中除了 `NFLSPC#6QIDONG` 恰出现一次以外，其它部分全部忘记。也即，输入的复制串仅可能为 `N Z H`，`Q N H`，`Q Z N` 三者之一。
- 子任务 2（$30$ 分）：保证所有复制串的 “后面” 段都是 `NFLSPC#6QIDONG`。也即，输入的复制串必然形如 `* * N`，其中 `*` 指代任意符合格式的输入。
- 子任务 3（$50$ 分）：无特殊限制。

Source：NFLSPC #6 J by Troverld

## 样例 #1

### 输入

```
3
N Z H
Q N H
Q Z N
```

### 输出

```
1
```

# 题解

## 作者：FFTotoro (赞：2)

典型的思路简单实现稍复杂的 trie + `map` 字符串模拟题。

使用官方题解做法；附参考代码。

下令 `S` 为 `string` 类型，`*` 为通配符。

显然 `N` 在后面的情况和 `N` 在前面的情况本质上是一样的，可以进行一些处理后用同一种方法做。但是记得**数组要清空**。

先考虑 `N` 在前面的情况，令记录串为 `NZH` 的形式：

1. `NZH` 在给定复制串中出现过，可以匹配的复制串有且仅有如下几种情况：

   - 复制串为 `NZH`：使用 `map<S,int>` 统计；
  
   - 复制串为 `NP*`，`P` 为 `ZH` 非空**真**前缀：使用字典树统计；
   
   - 复制串为 `N*S`，`S` 为 `ZH` 非空**真**后缀：同上；
   
   - 复制串为 `N**`：使用一个变量统计；

2. `NZH` 在给定复制串中未出现过（`NZ*` 和 `N*H` 出现过），可以匹配的复制串有且仅有如下几种情况：

   - 复制串为 `NP*`，`P` 为 `Z` 非空前缀：使用字典树统计；
   
   - 复制串为 `N*S`，`S` 为 `H` 非空后缀：同上；
   
   - 复制串为 `N**`：使用一个变量统计。

再考虑 `N` 在中间的情况，令记录串为 `QNH` 的形式：

1. `QNH` 在给定复制串中出现过，可以匹配的复制串有且仅有如下几种情况：

   - 复制串为 `QNH`：使用 `map<pair<S,S>,int>` 统计；
  
   - 复制串为 `QN*`：使用 `map<S,int>` 统计；
   
   - 复制串为 `*NH`：同上；
   
   - 复制串为 `*N*`：使用一个变量统计；

2. `QNH` 在给定复制串中未出现过（`QN*` 和 `*NH` 出现过），可以匹配的复制串有且仅有如下几种情况：

   - 复制串为 `QN*`：使用 `map<S,int>` 统计；
   
   - 复制串为 `*NH`：同上；
   
   - 复制串为 `*N*`：使用一个变量统计。

几种情况取个最大值即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef string S;
namespace Trie{
  int t[2][1000001][26],c[2][1000001],o[2];
  void C(){
    memset(t,0,sizeof(t));
    memset(c,0,sizeof(c));
    o[0]=o[1]=0;
  }
  void I(int b,S s){
    int p=0;
    for(char i:s)
      if(t[b][p][i-97])p=t[b][p][i-97];
      else p=t[b][p][i-97]=++o[b];
    c[b][p]++;
  }
  int Q(int b,S s){
    int p=0,w=0;
    for(char i:s)
      if(t[b][p][i-97])w+=c[b][p=t[b][p][i-97]];
      else break;
    return w;
  }
} // 字典树模板
int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<vector<pair<S,S> > > a(3);
  while(n--){
    S q,z,h; cin>>q>>z>>h;
    if(q=="N")a[0].emplace_back(z,h);
    else if(z=="N")a[1].emplace_back(q,h);
    else{
      if(q=="Q")q="H";
      else reverse(q.begin(),q.end());
      reverse(z.begin(),z.end());
      a[2].emplace_back(z,q);
      // 把 N 在后面的情况变成 N 在前面
    }
  } // 处理输入的字符串
  vector<int> c(3);
  for(int i=0;i<3;i++)
    if(int ca=0,cb=0,w=0;i&1){
      map<S,int> m1,m2;
      map<pair<S,S>,int> m3;
      for(auto [x,y]:a[i]){
        if(x!="Q"){
          if(y!="H")m3[make_pair(x,y)]++;
          else m1[x]++;
        }
        else if(y!="H")m2[y]++;
        else w++;
      } // 统计
      for(auto [x,y]:a[i]){
        if(x!="Q"){
          if(y!="H")c[i]=max(c[i],m1[x]+m2[y]+m3[make_pair(x,y)]);
          else ca=max(ca,m1[x]);
        }
        else if(y!="H")cb=max(cb,m2[y]);
      } // 计算答案
      c[i]=max(c[i],ca+cb)+w;
    } // N 在中间
    else{
      Trie::C();
      map<S,int> m;
      for(auto [x,y]:a[i]){
        S z=y; reverse(z.begin(),z.end());
        if(x!="Z"){
          if(y!="H")m[x+y]++;
          else Trie::I(0,x);
        }
        else if(y!="H")Trie::I(1,z);
        else w++;
      } // 统计
      for(auto [x,y]:a[i]){
        S e=x+y,r=e,z=y;
        reverse(r.begin(),r.end());
        reverse(z.begin(),z.end());
        e.pop_back(),r.pop_back();
        if(x!="Z"){
          if(y!="H")c[i]=max(c[i],m[x+y]+Trie::Q(0,e)+Trie::Q(1,r));
          else ca=max(ca,Trie::Q(0,x));
        }
        else if(y!="H")cb=max(cb,Trie::Q(1,z));
      } // 计算答案
      c[i]=max(c[i],ca+cb)+w;
    } // N 在前面
  cout<<*max_element(c.begin(),c.end())<<endl;
  return 0;
}
```

---

## 作者：JPGOJCZX (赞：0)

我~~hate~~love大力分讨。

这道题先分三种大情况：`N` 在左边，`N` 在中间，`N` 在右边。

声明：以下分类讨论中，`a, b, c, d` 均为记住的字符串。

# 记录操作

## `N` 在左边

- 当复制串形如 `N a b`，可以用 `map <string, int>` 记录。

- 当复制串形如 `N a H`，那么 `a` 就是 `a H` 的非空真前缀，可以将 `a` 顺序加入正串 trie 中。

- 当复制串形如 `N Z b`，那么 `b` 就是 `Z b` 的非空真后缀，将 `b` 和 `Z b` 都首尾颠倒后 `b` 就是 `Z b` 的非空真前缀，可以将 `b` 倒序加入反串 trie 中。

- 当复制串形如 `N Z H`，那么每个 `N` 在左边的复制串都可以与它匹配，直接累加答案。

## `N` 在右边

我们发现只要将整个字符串颠倒一下，如果有 `H`，将 `H` 变为 `Q`，就可以按照 `N` 在左边的方式处理字符串。

## `N` 在中间

- 当复制串形如 `a N b`，可以用 `map <pair <string, string>, int>` 记录。

- 当复制串形如 `Q N b`，可以用 `map <string, int>` 记录。

- 当复制串形如 `a N H`，可以用 `map <string，int>`记录。

- 当复制串形如 `Q N H`，那么每个 `N` 在中间的复制串都可以与它匹配，直接累加答案。

# 统计操作

将所有的复制串枚举一遍。

## `N` 在左边

- 当复制串形如 `N a b`，那么以下三种情况可以与其匹配：

1. `N c d`，其中 `a + b` = `c + d`，直接累加 `map[a + b]`；

2. `N c H`，其中 `c` 为 `a + b` 的前缀，比如 `N abcdefgh` 就与 `N abc H` 相匹配，在正串 trie 上求根到 `a + b` 的路径点权和；

3. `N Z d`，其中 `d` 为 `a + b` 的后缀，比如 `N abcdefgh` 就与 `N Z defgh` 相匹配，在反串 trie 上求根到 `a + b` 的路径点权和。

- 当复制串形如 `N a H`，为了不重复计算，只有形如 `N c H`，其中 `c` 为 `a` 的真前缀时才匹配，在正串 trie 上求根到 `a` 的路径点权和。

- 当复制串形如 `N Z b`，为了不重复计算，只有形如 `N Z d`，其中 `d` 为 `b` 的真后缀时才匹配，在反串 trie 上求根到 `b` 的路径点权和。

答案取第一种情况匹配数、第二三种情况匹配数和的最大值加上一开始统计的 `N Z H` 的个数。

## `N` 在右边

与记录操作一样，颠倒后按 `N` 在左边一样统计。

## `N` 在中间

- 当复制串形如 `a N b`，那么以下三种情况可以与其匹配：

1. `a N b`，直接累加 `map[pair(a, b)]`；

2. `a N H`，直接累加 `map[a]`；

3. `Q N b`，直接累加 `map[b]`。

- 当复制串形如 `Q N b`，直接累加 `map[b]`。

- 当复制串形如 `a N H`，直接累加 `map[a]`。

答案取第一种情况匹配数、第二三种情况匹配数和的最大值加上一开始统计的 `Q N H` 的个数。

这样就分类讨论完了所有情况。

完整代码~~是真的长~~：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 9;
int ch[5][N][26], red[5][N], tot[5], ans[5], n;
map <string, int> mp, mp5, mp2, mp3;//mp s1 = "N", mp5 s3 = "N", mp3, mp4, mp5 s2 == "N"
map <pair <string, string>, int> mp4;
string tmp, s1, s2, s3;
int num(char c){
	return c - 'a' + 1;
}
void insert(int ty){
	int u = 1, len = tmp.length();
	for(int i = 0; i < len; i++){
		int x = num(tmp[i]);
		if(ch[ty][u][x] == 0){
			ch[ty][u][x] = ++tot[ty];
			u = tot[ty];
		}
		else
			u = ch[ty][u][x];
	}
	red[ty][u]++;
}
int query(int ty){
	int u = 1, ans = 0, len = tmp.length();
	for(int i = 0; i < len; i++){
		int x = num(tmp[i]);
		if(ch[ty][u][x]){
			ans += red[ty][ch[ty][u][x]];
			u = ch[ty][u][x];
		} else
			break;
	}
	return ans;
}
/*
ty = 1 : s1 == "N",正串;
ty = 2 : s1 == "N",反串;
ty = 3 : s3 == "N",正串;
ty = 4 : s3 == "N",反串
*/
struct Store{
	string t1, t2, t3;
} st[5][N];
int cnt[5];
signed main(){
	for(int i = 0; i <= 8; i++)
		tot[i] = 1;
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++){
		cin >> s1 >> s2 >> s3;
		if(s1 == "N")
			st[1][++cnt[1]] = Store{s1, s2, s3};
		else if(s2 == "N")
			st[2][++cnt[2]] = Store{s1, s2, s3};
		else
			st[3][++cnt[3]] = Store{s1, s2, s3};
	}
	for(int i = 1; i <= 3; i++){
		int w = 0, cnta = 0, cntb = 0;
		if(i == 1){
			for(int j = 1; j <= cnt[i]; j++){
				s1 = st[i][j].t1;
				s2 = st[i][j].t2;
				s3 = st[i][j].t3;
				if(s2 != "Z" && s3 != "H"){
					tmp = s2 + s3;
					mp[tmp]++;
				} else if(s2 == "Z" && s3 != "H"){
					tmp = s3;
					reverse(tmp.begin(), tmp.end());
					insert(2);
				} else if(s2 != "Z" && s3 == "H"){
					tmp = s2;
					insert(1);
				} else
					w++;
			}
			for(int j = 1; j <= cnt[i]; j++){
				s1 = st[i][j].t1;
				s2 = st[i][j].t2;
				s3 = st[i][j].t3;
				if(s2 != "Z" && s3 != "H"){
					int sum = mp[s2 + s3];
					tmp = s2 + s3;
					tmp.pop_back();
					sum += query(1);
					tmp = s2 + s3;
					reverse(tmp.begin(), tmp.end());
					tmp.pop_back();
					sum += query(2);
					ans[i] = max(ans[i], sum);
				} else if(s2 == "Z" && s3 != "H"){
					tmp = s3;
					reverse(tmp.begin(), tmp.end());
					cntb = max(cntb, query(2));
				} else if(s2 != "Z" && s3 == "H"){
					tmp = s2;
					cnta = max(cnta, query(1));
				}
			}
			ans[i] = max(ans[i], cnta + cntb) + w;
		} else if(i == 2){
			for(int j = 1; j <= cnt[i]; j++){
				s1 = st[i][j].t1;
				s2 = st[i][j].t2;
				s3 = st[i][j].t3;
				if(s1 != "Q" && s3 != "H")
					mp4[make_pair(s1, s3)]++;
				else if(s1 == "Q" && s3 != "H")
					mp3[s3]++;
				else if(s1 != "Q" && s3 == "H")
					mp2[s1]++;
				else
					w++;
			}
			for(int j = 1; j <= cnt[i]; j++){
				s1 = st[i][j].t1;
				s2 = st[i][j].t2;
				s3 = st[i][j].t3;
				if(s1 != "Q" && s3 != "H")
					ans[i] = max(ans[i], mp2[s1] + mp3[s3] + mp4[make_pair(s1, s3)]);
				else if(s1 == "Q" && s3 != "H")
					cntb = max(cntb, mp3[s3]);
				else if(s1 != "Q" && s3 == "H")
					cnta = max(cnta, mp2[s1]);
			}
			ans[i] = max(ans[i], cnta + cntb) + w;
		} else {
			for(int j = 1; j <= cnt[i]; j++){
				s1 = st[i][j].t1;
				s2 = st[i][j].t2;
				s3 = st[i][j].t3;
				if(s1 == "Q")
					s1 = "H";
				reverse(s1.begin(), s1.end());
				reverse(s2.begin(), s2.end());
				string fk = s1;
				s1 = s2;
				s2 = fk;
				st[i][j].t1 = s1;
				st[i][j].t2 = s2;
				if(s1 != "Z" && s2 != "H"){
					tmp = s1 + s2;
					mp[tmp]++;
				} else if(s1 == "Z" && s2 != "H"){
					tmp = s2;
					reverse(tmp.begin(), tmp.end());
					insert(4);
				} else if(s1 != "Z" && s2 == "H"){
					tmp = s1;
					insert(3);
				} else
					w++;
			}
			for(int j = 1; j <= cnt[i]; j++){
				s1 = st[i][j].t1;
				s2 = st[i][j].t2;
				s3 = st[i][j].t3;
				if(s1 != "Z" && s2 != "H"){
					int sum = mp[s1 + s2];
					tmp = s1 + s2;
					tmp.pop_back();
					sum += query(3);
					tmp = s1 + s2;
					reverse(tmp.begin(), tmp.end());
					tmp.pop_back();
					sum += query(4);
					ans[i] = max(ans[i], sum);
				} else if(s1 == "Z" && s2 != "H"){
					tmp = s2;
					reverse(tmp.begin(), tmp.end());
					cntb = max(cntb, query(4));
				} else if(s1 != "Z" && s2 == "H"){
					tmp = s1;
					cnta = max(cnta, query(3));
				}
			}
			ans[i] = max(ans[i], cnta + cntb) + w;
		}	
	}
	printf("%lld", max(max(ans[1], ans[2]), ans[3]));
	return 0;
}
```

---

