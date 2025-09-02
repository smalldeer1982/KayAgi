# Card Game

## 题目描述

两名玩家正在玩在线纸牌游戏。游戏使用一副  $32$ 张牌进行。每张牌都有花色和数字。有四种花色：梅花、方块、红心和黑桃。用字符 `C`、`D`、`H` 和 `S` 分别表示它们。共有 8 种数字，按递增顺序为 `2`、`3`、`4`、`5`、`6`、`7`、`8`、`9`。

每张牌由两个字母表示：其等级和花色。例如，红心 8 可以表示为 `8H`。

在游戏开始时，会选择一种花色作为王牌花色。

在每一轮中，玩家的操作如下：第一个玩家在桌子上放一张牌，第二个玩家必须用自己的一张牌打败这张牌。之后，两张牌都被移动到弃牌堆中。

一张牌可以打败另一张牌，如果两张牌都具有相同的花色，并且第一张牌的等级比第二张牌高。例如，方块 8 可以打败方块 4。此外，王牌可以打败任何非王牌牌，无论牌的等级如何，例如，如果王牌花色是梅花 (`C`)，那么梅花 3 可以打败方块 9。请注意，王牌只能被等级更高的王牌打败。

游戏中进行了 $n$ 轮，因此弃牌堆现在包含 $2n$ 张牌。你想要重建游戏中进行的轮次，但是弃牌堆中的牌已经洗牌。找到可能在游戏中玩过的 $n$ 轮的任何可能顺序。

## 样例 #1

### 输入

```
8
3
S
3C 9S 4C 6D 3S 7S
2
C
3S 5D 9S 6H
1
H
6C 5D
1
S
7S 3S
1
H
9S 9H
1
S
9S 9H
1
C
9D 8H
2
C
9C 9S 6H 8C```

### 输出

```
3C 4C
6D 9S
3S 7S
IMPOSSIBLE
IMPOSSIBLE
3S 7S
9S 9H
9H 9S
IMPOSSIBLE
6H 9C
9S 8C```

# 题解

## 作者：信息向阳花木 (赞：5)

模拟。把每个花色的牌排序。只要 A 出牌， B 有能打 A 的牌就可以了。我们可以先在每个花色内，小的分给 A，大的分给 B。如果一个花色数量是奇数，我们就用王牌来打他。如果王牌不够用（奇数牌的种类数量大于王牌总数量）就输出无解。

思路就这样，细节看代码吧。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int N = 200010;

int t, n, cnt[5]; // cnt 表示每种花色的数量
char c;
char s[N][5];
pair<int, int> p[5][N]; // p[i][j] 表示花色为 i 的第 j 张牌的数字和编号
vector<int> A, B; // 存储 A, B 的牌
map<char, int> mp;

int main()
{
	mp['C'] = 1;
	mp['D'] = 2;
	mp['H'] = 3;
	mp['S'] = 4;
	scanf("%d", &t);
	while (t -- )
	{
		memset(cnt, 0, sizeof cnt);
		scanf("%d", &n);
		cin >> c;
		for (int i = 1; i <= n * 2; i ++ ) cin >> (s[i] + 1);
		for (int i = 1; i <= n * 2; i ++ )
		{
			int tot = ++ cnt[mp[s[i][2]]];
			p[mp[s[i][2]]][tot] = {s[i][1] - '0', i};
			// 储存这张牌的数字和编号
		}
		A.clear(); B.clear();
		sort(p[1] + 1, p[1] + cnt[1] + 1);
		sort(p[2] + 1, p[2] + cnt[2] + 1);
		sort(p[3] + 1, p[3] + cnt[3] + 1);
		sort(p[4] + 1, p[4] + cnt[4] + 1);
		// 每种花色按数字大小升序排序
		int tot = 0;
		for (int i = 1; i <= 4; i ++ )
			if(cnt[i] & 1 && mp[c] != i) tot ++;
		if(tot > cnt[mp[c]]) // 王牌数量不够用
		{
			puts("IMPOSSIBLE");
			continue;
		}
		bool flag = 1;
		for (int i = 1; i <= 4; i ++ )
		{
			if(!cnt[i]) continue;
			if(cnt[i] % 2 == 0 && i != mp[c]) // 当前花色牌的数量是偶数，内部解决
			{
				int l = 1, r = cnt[i];
				while (l <= r)
				{
					A.push_back(p[i][l].second);
					B.push_back(p[i][r].second);
					l ++, r --;
					// 小的给 A，大的给 B
				}
			}
		}
		int L = 1;
		for (int i = 1; i <= 4; i ++ )
		{
			if(!cnt[i]) continue;
			if((cnt[i] & 1) && mp[c] != i) // 奇数牌
			{
				int l = 1, r = cnt[i];
				while (l < r)
				{
					A.push_back(p[i][l].second);
					B.push_back(p[i][r].second);
					l ++, r --;
				}
				A.push_back(p[i][l].second); // 最后一张给 A，B 用王牌
				B.push_back(p[mp[c]][L].second); L ++;
			}
		}
		int r = cnt[mp[c]];
		while (L <= r)
		{
			A.push_back(p[mp[c]][L].second);
			B.push_back(p[mp[c]][r].second);
			L ++, r --;
		} // 剩下的王牌小的给 A，大的给 B
		for (int i = 0; i < n; i ++ )
		{
			int x = A[i], y = B[i];
			cout << s[x][1] << s[x][2] << ' ' << s[y][1] << s[y][2] << '\n';
		}
	}
	return 0;
}
```

---

## 作者：xiaoyang111 (赞：2)

### 前言 

[洛谷题目传送门。](https://www.luogu.com.cn/problem/CF1932D)

[题目机翻后的大意。](https://www.luogu.com.cn/paste/dq8i4xbp)

[可能更好的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/cf1932d-ti-xie)

### 思路

题目是要求给出一种可能出现的回合。

我们从题中知道了，除了王牌花色其他的牌中只有花色相同的才能互相攻击，且只有点数大的攻击点数小的。

那么我们可以考虑通过以下策略进行构造可能出现的回合：

1. 我们先把同一花色的牌放到一起，先让不是王牌花色的牌进行两两攻击，让每一种花色两两组队攻击后只剩下 $1$ 张或 $0$ 张牌。

2. 如果有剩下的牌，把所有剩下的牌放到一起，每一个牌都和王牌花色的牌两两组队攻击。如果剩下的牌比王牌数量还多，那么就是无解。

3. 最后如果王牌花色的牌还有剩余，那么让王牌花色剩下的牌两两攻击。

但要注意，每次两张牌互相攻击第一张是比第二张牌小的，所以说先把每一种花色的牌放到一起后排个序，组队攻击的时候从左到右组就可以了。

### 代码

下面是代码。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#define int long long
using namespace std;
void solve(){
	int n;
	cin >> n;
	char c;
	cin >> c;
	unordered_map<char,vector<int>> m;//分组后的结果。
	string str; 
	for (int i=0;i<2*n;++i){
		cin >> str;
		m[str[1]].emplace_back(str[0]-'0');//分组。
	}
	vector<string> t;
	vector<string> ans;//先把第一步搞完后的答案记在一个地方因为不确定无解。
	for (auto &item : m){//执行第一步。
		sort(item.second.begin(),item.second.end());//排序。
		if (item.first!=c){
			for (int i=0;i<item.second.size()/2;++i){
				ans.emplace_back(to_string(item.second[i*2])+item.first+" "+
				to_string(item.second[i*2+1])+item.first);
			}
			if (item.second.size()&1){
				t.emplace_back(to_string(item.second[item.second.size()-1])+item.first);
			}
		}
	} 
	if (t.size()>m[c].size()){//无解。
		cout<<"IMPOSSIBLE"<<endl;
	}else{
		int i;
		for (const auto &item : ans){//先把第一步的答案输出。
			cout<<item<<endl;
		}
		for (i=0;i<t.size();++i){//第二步。
			cout<<t[i]<<" "<<m[c][i]<<c<<endl;
		}
		for (;i<m[c].size();i+=2){//第三步。
			cout<<m[c][i]<<c<<" "<<m[c][i+1]<<c<<endl;
		}
	}
}
signed main(){
	int T;
	cin >> T;
	for (int _=0;_<T;++_){
		solve();
	}
	return 0;
}
//qwq
```

---

## 作者：2huk (赞：2)

### Solution

首先我们将非王牌花色的每种花色两两配对。

此时可能会剩下一些牌，再把这些牌和王牌花色配对。

最后把剩下的王牌花色两两配对。

在模拟上述过程时判断是否无解即可。

### Code

```cpp
map<char, int> mp({{'S', 0}, {'C', 1}, {'H', 2}, {'D', 3}});
map<int, char> pm({{0, 'S'}, {1, 'C'}, {2, 'H'}, {3, 'D'}});
 
void solve() {
	int n = read();
	char c; cin >> c;
	int BIG = mp[c];
	vector<int> a[4] = {{}, {}, {}, {}};
	for (int i = 1; i <= 2 * n; ++ i ) {
		string str; cin >> str;
		a[mp[str[1]]].push_back(str[0] - '0');
	}
	
	fup (i, 0, 3) {
		if (a[i].size()) sort(a[i].begin(), a[i].end());
	}
	
	int k = 0;
	fup (i, 0, 3) 
		if (i != BIG) k += a[i].size() % 2;
	
	if (a[BIG].size() >= k && (a[BIG].size() - k) % 2 == 0) {
		fup (i, 0, 3) if (i != BIG) {
			int len = a[i].size();
			for (int j = 0; j + 1 < len; j += 2 ) {
				cout << a[i][j] << pm[i] << ' ' << a[i][j + 1] << pm[i] << '\n';
			}
			if (len % 2) {
				cout << a[i].back() << pm[i] << ' ' << a[BIG].back() << c << '\n';
				a[BIG].pop_back();
			}
		}
		int x = a[BIG].size();
		for (int i = 0; i + 1 < x; i += 2 ) {
			cout << a[BIG][i] << c << ' ' << a[BIG][i + 1] << c << '\n';
		}
	}
	else puts("IMPOSSIBLE");
}
```

---

## 作者：awesomegordon (赞：1)

### CF1932D题解

awesomegordon 原创。

这个题的主要思路不是多么难，就是一个贪心，稍加模拟就好了。

#### 思路

我们先把王牌单独拎出来不说，先把其他花色整理好，最后该花色奇数数量牌的，用一个王牌，好让他们“成双成对”地匹配。

需要注意的是，在这个过程中，王牌可能不够用了，于是输出无解情况。

最后单独排序王牌就好了，更详细的，代码里会说。

#### 代码

码风丑，勿喷。



```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[10][100];
int coltrans(char x){
	if(x=='C'){
		return 1;
	}
	if(x=='D'){
		return 2;
	}
	if(x=='H'){
		return 3;
	}
	if(x=='S'){
		return 4;
	}
}
char numtrans(int x){
	if(x==1){
		return 'C';
	}
	if(x==2){
		return 'D';
	}
	if(x==3){
		return 'H';
	}
	if(x==4){
		return 'S';
	}	
}
void solve(){
	int n;
	cin>>n;
	n=n*2;
	char joker;
	cin>>joker;
	int jk=coltrans(joker);
	
	int cnt[10]={0,0,0,0,0};
	for(int i=1;i<=n;i++){
		char temp1;
		char temp2;
		cin>>temp1>>temp2;
		a[coltrans(temp2)][++cnt[coltrans(temp2)]]=temp1-'0';
	}
	for(int i=1;i<=4;i++){
		sort(a[i],a[i]+cnt[i]+1);
	}
	int ps=0;
	for(int i=1;i<=4;i++){
		if(i!=jk&&cnt[i]%2==1){
			ps++;
		}
	}
	if(ps>cnt[jk]){
		cout<<"IMPOSSIBLE"<<"\n";
		return ;
	} 
	
	int now_used=0;
	for(int i=1;i<=4;i++){
		if(i==jk){
			continue;
		} 
		if(cnt[i]%2==1){
			for(int j=1;j<=cnt[i]-1;j+=2){
				printf("%d%c ",a[i][j],numtrans(i));
				printf("%d%c\n",a[i][j+1],numtrans(i));
			}
			printf("%d%c ",a[i][cnt[i]],numtrans(i));
			printf("%d%c\n",a[jk][++now_used],numtrans(jk));
		}else{
			for(int j=1;j<=cnt[i];j+=2){
				printf("%d%c ",a[i][j],numtrans(i));
				printf("%d%c\n",a[i][j+1],numtrans(i));
			}		
		}
	}
	for(int i=now_used+1;i<=cnt[jk];i+=2){
		printf("%d%c %d%c\n",a[jk][i],numtrans(jk),a[jk][i+1],numtrans(jk));
	}
	return ;
	
}
int main(){
	int T;
	cin>>T;
	while(T--){
		solve();
	} 
	return 0;
}
```

---

## 作者：hstt (赞：1)

## 简要题意
按以下规则配对牌堆：
- 若为同种花色，配对为一个点数小的和一个点数大的。
- 若为不同花色，使后一种花色为主要花色即可。

## 思路
显然，先在每个非主要花色内部选取两个，直到个数少于 $2$。若剩余 $1$ 个，选一张主要花色与当前牌配对。

最后，配对主要花色，记得判断无解。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
char s[18][3],t[3],lzm[3];
priority_queue<int,vector<int>,greater<int> >q[4];
vector<pair<char,char> >ans;
void cq(int k){//清空牌堆
    while(!q[k].empty())q[k].pop();
}
int hs(char ch){
    if(ch=='C')return 0;
    if(ch=='D')return 1;
    if(ch=='H')return 2;
    return 3;
}
bool calc(int p,char s){
    while(q[p].size()>1){
        ans.push_back({s,q[p].top()+'0'});
        q[p].pop();
        ans.push_back({s,q[p].top()+'0'});
        q[p].pop();
    }
    if(!q[p].empty()){
        if(p==m||q[m].empty())return 0;
        ans.push_back({s,q[p].top()+'0'});
        ans.push_back({lzm[0],q[m].top()+'0'});
        q[p].pop();
        q[m].pop();
    }
    return 1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        ans.clear();
        cq(0);cq(1);cq(2);cq(3);
        scanf("%d%s",&n,lzm);
        m=hs(lzm[0]);
        for(int i=1;i<=n*2;i++){
            scanf("%s",t);
            q[hs(t[1])].push(t[0]-'0');
        }
        if(m!=0)
            if(!calc(0,'C')){//分别计算
                puts("IMPOSSIBLE");
                continue;
            }
        if(m!=1)
            if(!calc(1,'D')){
                puts("IMPOSSIBLE");
                continue;
            }
        if(m!=2)
            if(!calc(2,'H')){
                puts("IMPOSSIBLE");
                continue;
            }
        if(m!=3)
            if(!calc(3,'S')){
                puts("IMPOSSIBLE");
                continue;
            }
        if(!calc(m,lzm[0])){
            puts("IMPOSSIBLE");
        }else{
            for(int i=0;i<ans.size();i+=2){
                printf("%c%c %c%c\n",ans[i].second,ans[i].first,ans[i+1].second,ans[i+1].first);
            }
        }
    }
    return 0;
}
```

---

## 作者：tallnut (赞：1)

贪心+大%你。
# 思路
因为只有王牌或者同一花色的可以互相杀，先让除王牌以外的其他花色牌自相残杀。这样可以把这些花色牌的张数消到 $1$ 或者 $0$。如果是 $1$ 的话就动用一张王牌把他干掉。王牌不够用就无解。到最后让剩下的王牌自相残杀即可。
# AC 代码
[赛时 AC 代码](https://www.luogu.com.cn/record/148346103)。
```
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cctype>
using namespace std;
const int N = 40;
int t,n;
char trump;
struct card
{
	char suit;
	int rank;
} cards[N];
void readcard(int index)
{
	char c = getchar();
	while (!isdigit(c))
		c = getchar();
	cards[index].rank = c - '0';
	c = getchar();
	cards[index].suit = c;
}
//把花色映射到整型
int convert(char cc)
{
	switch (cc)
	{
		case 'C':
			return 1;
			break;
		case 'D':
			return 2;
			break;
		case 'H':
			return 3;
			break;
		default:
			return 4;
			break;
	}
}
char convert2(int nn)
{
	switch (nn)
	{
		case 1:
			return 'C';
			break;
		case 2:
			return 'D';
			break;
		case 3:
			return 'H';
			break;
		default:
			return 'S';
			break;
	}
}
/*
思路：
普通花色的牌只能互相消，但是trump可以吊打其他花色。
所以如果其他花色的数量为偶，就可以自己消掉，不需要动用trump来插手
否则就需要一张trump来干掉
*/
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> trump;
		memset(cards,0,sizeof cards);
		for (int i = 1;i <= (n << 1);i++)
			readcard(i);
		vector<int> cards2[10];
		//按照花色分类
		for (int i = 1;i <= (n << 1);i++)
			cards2[convert(cards[i].suit)].push_back(cards[i].rank);
		//为了方便，排序
		for (int i = 1;i <= 4;i++)
			sort(cards2[i].begin(),cards2[i].end());
		//最少需要动用几张trump
		int cnt = 0;
		for (int i = 1;i <= 4;i++)
			if (i != convert(trump) && (cards2[i].size() & 1) == 1) cnt++;
		//如果trump不够用了就不行
		if (cnt > cards2[convert(trump)].size()) cout << "IMPOSSIBLE" << endl;
		else
		{
			//先把其他花色消到只剩0/1
			int leftcnt[10];
			card left[10];
			for (int i = 1;i <= 4;i++)
			{
				if (i == convert(trump)) continue;
				for (int j = 0;j + 1 < cards2[i].size();j += 2)
				{
					cout << cards2[i][j] << convert2(i) << ' ';
					cout << cards2[i][j + 1] << convert2(i) << endl;
				}
				if ((cards2[i].size() & 1) == 1)
				{
					leftcnt[i] = 1;
					left[i] = {convert2(i),cards2[i][cards2[i].size() - 1]};
				}
				else leftcnt[i] = 0;
			}
			//接着动用trump消掉那些剩余的牌
			int curtrump = 0;
			for (int i = 1;i <= 4;i++)
				if (i != convert(trump) && leftcnt[i] == 1)
				{
					cout << left[i].rank << left[i].suit << ' ';
					cout << cards2[convert(trump)][curtrump] << trump << endl;
					curtrump++;
				}
			//接着再消掉trump本身
			for (int i = curtrump;i < cards2[convert(trump)].size();i += 2)
			{
				cout << cards2[convert(trump)][i] << trump << ' ';
				cout << cards2[convert(trump)][i + 1] << trump << endl;
			}
		}
	}
}
```

---

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/CF1932D)

## 思路

考虑贪心。先对所有牌从小到大进行排序，如果两张牌一张王牌一张非王牌，则王牌大于非王牌。如果两张牌花色相同，则按数字大小排序。如果两张牌花色不同且都不是王牌花色，则按照花色的字典序排序。

然后对于排序后的每两张相邻的牌，如果花色相同，那么一定可以凑成一对，否则只能和王牌花色凑。如果出现了相邻两张牌花色不匹配且已经没有王牌花色的牌时，输出无解。

两次遍历排序后的牌堆，第一次判断是否有解，第二次输出结果。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>
 
using namespace std;
 
const int kMaxN = 16 + 5;
 
int t, n, C, D, H, S;
char k;
 
struct Card {
  int c;
  char s;
  friend bool operator<(const Card& a, const Card& b) {
    if (a.s != k && b.s == k) {
      return 1;
    }
    if (a.s == k && b.s != k) {
      return 0;
    }
    return (a.s != b.s ? a.s < b.s : a.c < b.c);
  }
};
 
Card a[kMaxN << 1];
 
int main() {
  for (cin >> t; t; t--) {
    C = D = H = S = 0;
    cin >> n >> k;
    for (int i = 1; i <= (n << 1); i++) {
      string p;
      cin >> p;
      a[i] = (Card){p[0] - '0', p[1]};
      C += p[1] == 'C', D += p[1] == 'D';
      H += p[1] == 'H', S += p[1] == 'S';
    }
    sort(a + 1, a + (n << 1) + 1);
    int flag = 0, P = n << 1, tmp = (k == 'C' ? C : (k == 'D' ? D : (k == 'H' ? H : S)));
    for (int i = 1; i <= P; i++) {
      if (a[i].s == a[i + 1].s) {
        i++;
        continue;
      }
      if (tmp > 0) {
        tmp--, P--;
        continue;
      }
      flag = 1;
      break;
    }
    if (flag) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    P = n << 1;
    for (int i = 1; i <= P; i++) {
      if (a[i].s == a[i + 1].s) {
        cout << a[i].c << a[i].s << ' ' << a[i + 1].c << a[i + 1].s << '\n';
        i++;
        continue;
      }
      cout << a[i].c << a[i].s << ' ' << a[P].c << a[P].s << '\n';
      P--;
    }
  }
  return 0;
}
```

---

## 作者：LiJoQiao (赞：1)

一道贪心题。  

由于数据不会出现同色同大小的牌，所以出现两个同色的牌一定可以分为一个回合。  

由题意得非王牌花色的牌只能由同色更大的牌或王牌花色的任意一张打败，而王牌花色的只能由同色更大的牌打败，可以看出王牌花色比较全能，跟任意牌都可以组成一个回合，这里贪心尽量减少使用王牌花色的牌来解决其他花色的牌，把王牌花色留给没有同色的牌可组成一个回合的牌。  

我们把牌按花色分开，将大小排序，然后把除王牌花色的都两两组成一个回合，剩余的用王牌花色解决，最后可能会剩下王牌花色的牌，让它们也两两结合即可。  
如这个过程王牌花色的牌不够用，说明无解。  

代码如下。  

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr char col[4]={'C','D','H','S'};
map<char,int> colmp;
int c[4][40],p[4],ansp;
int n;char wp,cinnum,cincol;
struct Card{
    int num;
    char col;
}ans[20][2];
void init(){
    ansp=0;
    for(int i=0;i<4;++i)p[i]=0;
}
void solve(){
    init();
    cin>>n>>wp;
    for(int i=1;i<=(n<<1);++i){
        cin>>cinnum>>cincol;
        c[colmp[cincol]][++p[colmp[cincol]]]=cinnum-'0';
    }
    for(int i=0;i<4;++i){
        sort(c[i],c[i]+p[i]+1);
        if(i==colmp[wp])continue;
        while(p[i]>1){
            ++ansp;
            ans[ansp][0]={c[i][p[i]-1],col[i]};ans[ansp][1]={c[i][p[i]],col[i]};
            p[i]-=2;
        }
        if(p[i]==1){
            if(!p[colmp[wp]]){puts("IMPOSSIBLE");return;}
            else{
                ++ansp;
                ans[ansp][0]={c[i][p[i]],col[i]};ans[ansp][1]={c[colmp[wp]][p[colmp[wp]]],wp};--p[colmp[wp]];
            }
            --p[i];
        }
    }
    while(p[colmp[wp]]){
        ++ansp;
        ans[ansp][0]={c[colmp[wp]][p[colmp[wp]]-1],wp};ans[ansp][1]={c[colmp[wp]][p[colmp[wp]]],wp};
        p[colmp[wp]]-=2;
    }
    for(int i=1;i<=n;++i){
        printf("%d%c %d%c\n",ans[i][0].num,ans[i][0].col,ans[i][1].num,ans[i][1].col);
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    for(int i=0;i<4;++i)colmp[col[i]]=i;
    int T114514;cin>>T114514;while(T114514--)solve();
    return 0;
}
```



---

## 作者：IOI_official (赞：0)

贪心题。

我们可以先把王牌放在一边，将普通牌的每一种花色按照数字从大到小排好，这样它们就可以互相抵消，最后每一组花色都会剩下 0 或 1 张牌，再用王牌将它们杀掉，如果王牌不够用，也就是说剩下的普通牌的数量比王牌多，就无解，输出 `IMPOSSIBLE`。

---

## 作者：D_C_Z (赞：0)

### 一些鲜花
当天晚上 vp 切了 AB 然后卡 C。

遂做 D。

然后一眼秒了，于是开启了痛苦的调模拟历程。

省流：回去秒了 C 但 D 调到下考没整出来。

滚回来写 tj 了。
## solution
首先，注意到不同花色之间是不可以对打的，所以我们只需要逐个击破各个花色。

其次，在同花色为偶数的情况下肯定不需要借助王牌，因为没有相同的牌一张一张对应就行了。

奇数拿一张王牌来把它变成偶数就行了。

然后用剩下的王牌继续一张一张对应。

判无解就看王牌够不够清理掉所有剩余的情况。

或者王牌剩余的为奇数。

然后就是抽象码力题了
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,f[200001],cnt,mx,y,m,ans,t,K;
string ph[201];
int sb[4]={3,4,8,19};
string bl[33],KinG;
struct dcz{
	string x,y;
}an[10001];
struct wssb{
	int x;
	string y;
}p[21][201],a[201];
bool cmp(wssb x,wssb y){
	return x.x<y.x;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>KinG;
		int ptt,tot,cnt=0;
		ptt=tot=0;
		f[3]=f[4]=f[8]=f[19]=0;
		K=KinG[0]-'A'+1;
		for(int i=1;i<=2*n;i++){
			cin>>bl[i];
			if(bl[i][1]==KinG[0]){
				a[++cnt].x=bl[i][0]-'0';
				a[cnt].y=bl[i];
			}
			else{
				p[bl[i][1]-'A'+1][++f[bl[i][1]-'A'+1]].x=bl[i][0]-'0';
				p[bl[i][1]-'A'+1][f[bl[i][1]-'A'+1]].y=bl[i];
			}
			
		}
		for(int i=0;i<4;i++){
			if(f[sb[i]]&&f[sb[i]]%2==0&&sb[i]!=K){
				sort(p[sb[i]]+1,p[sb[i]]+f[sb[i]]+1,cmp);
				for(int j=1;j<f[sb[i]];j+=2){
					an[++tot].x=p[sb[i]][j+1].y;
					an[tot].y=p[sb[i]][j].y;
				}
			}
			else if(f[sb[i]]&&sb[i]!=K){
				sort(p[sb[i]]+1,p[sb[i]]+f[sb[i]]+1,cmp);
				for(int j=1;j<f[sb[i]]-1;j+=2){
					an[++tot].x=p[sb[i]][j+1].y;
					an[tot].y=p[sb[i]][j].y;
				}
				ph[++ptt]=p[sb[i]][f[sb[i]]].y;
			}
		}
		if(ptt>cnt||(cnt-ptt)%2==1) {cout<<"IMPOSSIBLE"<<endl; continue;}
		sort(a+1,a+cnt+1,cmp);
		for(int i=1;i<=ptt;i++){
			an[++tot].x=a[i].y;
			an[tot].y=ph[i];
		}
		for(int i=ptt+1;i<cnt;i+=2){
			an[++tot].x=a[i+1].y;
			an[tot].y=a[i].y;
		}
		for(int i=1;i<=tot;i++){
			cout<<an[i].y<<" "<<an[i].x<<endl;
		}
	}
	return 0;
}//stOstOstO%%%vanyou%%%OrzOrzOrz
```

---

## 作者：minVan (赞：0)

**题目大意**

有 $2n$ 张牌，每张牌有各自的点数和花色（$2\sim9$ 和 $\texttt{C,D,H,S}$），还有王牌花色 $c\in\{\texttt{C,D,H,S}\}$。

对于两张牌 $xA,yB$：
- 若 $A\neq B$ 且均不为 $c$，则不可比较；
- 若 $A\neq B=c$，则 $yB$ 胜；
- 若 $A=B$，则 $x,y$ 中大的那张牌获胜。

问是否能打 $n$ 个回合。

**解题思路**

用四个小根堆存放每种花色的每张牌的点数，对于 $d\neq c$，则每次取出两次堆顶进行比较，并删除它们两个元素。

剩下的非王牌花色元素都与王牌比较，如果王牌个数不够，则输出 `IMPOSSIBLE`；否则匹配完所有非王牌后再在王牌里逐一两两匹配即可。


**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
const int N = 40;
map<char, priority_queue<int> > mp;
vector<pair<pair<int, char>, pair<int, char> > > ans;
int n;
char c;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    mp.clear();
    ans.clear();
    cin >> n >> c;
    int cnt = 0;
    for(int i = 1; i <= n * 2; i++) {
      string s;
      cin >> s;
      mp[s[1]].push('0' - s[0]);
    }
    if(c != 'C') {
      while(mp['C'].size() >= 2) {
        int t1 = -mp['C'].top();
        mp['C'].pop();
        int t2 = -mp['C'].top();
        mp['C'].pop();
        ans.push_back({{t1, 'C'}, {t2, 'C'}});
      }
      cnt += mp['C'].size();
    }
    if(c != 'D') {
      while(mp['D'].size() >= 2) {
        int t1 = -mp['D'].top();
        mp['D'].pop();
        int t2 = -mp['D'].top();
        mp['D'].pop();
        ans.push_back({{t1, 'D'}, {t2, 'D'}});
      }
      cnt += mp['D'].size();
    }
    if(c != 'H') {
      while(mp['H'].size() >= 2) {
        int t1 = -mp['H'].top();
        mp['H'].pop();
        int t2 = -mp['H'].top();
        mp['H'].pop();
        ans.push_back({{t1, 'H'}, {t2, 'H'}});
      }
      cnt += mp['H'].size();
    }
    if(c != 'S') {
      while(mp['S'].size() >= 2) {
        int t1 = -mp['S'].top();
        mp['S'].pop();
        int t2 = -mp['S'].top();
        mp['S'].pop();
        ans.push_back({{t1, 'S'}, {t2, 'S'}});
      }
      cnt += mp['S'].size();
    }
    if(mp[c].size() < cnt) { cout << "IMPOSSIBLE\n"; continue; }
    if(c != 'C') {
      while(!mp['C'].empty()) {
        cout << -mp['C'].top() << "C " << -mp[c].top() << c << '\n';
        mp['C'].pop(), mp[c].pop();
      }
    }
    if(c != 'D') {
      while(!mp['D'].empty()) {
        cout << -mp['D'].top() << "D " << -mp[c].top() << c << '\n';
        mp['D'].pop(), mp[c].pop();
      }
    }
    if(c != 'H') {
      while(!mp['H'].empty()) {
        cout << -mp['H'].top() << "H " << -mp[c].top() << c << '\n';
        mp['H'].pop(), mp[c].pop();
      }
    }
    if(c != 'S') {
      while(!mp['S'].empty()) {
        cout << -mp['S'].top() << "S " << -mp[c].top() << c << '\n';
        mp['S'].pop(), mp[c].pop();
      }
    }
    while(!mp[c].empty()) {
      int t1 = -mp[c].top();
      mp[c].pop();
      int t2 = -mp[c].top();
      mp[c].pop();
      cout << t1 << c << " " << t2 << c << '\n';
    }
    for(auto i : ans) {
      cout << i.fi.fi << i.fi.se << ' ' << i.se.fi << i.se.se << '\n';
    }
  }
  return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1932D Card Game](https://www.luogu.com.cn/problem/CF1932D)

### 思路

先忽略大小关系，考虑怎样才能成功打出每一对牌，显然是同字母或有一张是王牌。

想到非王牌只能配对同字母牌，于是我们先配对非王牌的同字母牌，并且尽可能多的配对。此时对于非王牌，有两种情况：如果牌数为奇数，那么会多出一张，显然，这是无法避免的最好情况；为偶数，那么恰好完全匹配。多出来的那一张牌，显然我们只能用一张王牌配对。此时如果王牌数量小于失配的牌的数量，显然无解。否则配对后由于总牌数是偶数，那么剩余的王牌数量也一定是偶数，恰好能配对。

输出配对时注意一下，大的牌放在后面即可。

时间复杂度 $O(tn)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using std::cin;using std::cout;
constexpr int N=18;
int t,n,k;
struct A{int a,b,c,d;}b[N];
char c;
std::string s;
std::vector<int>a[5];
inline int turn(char c){//字符转数字
	if(c=='C') return 1;
	if(c=='D') return 2;
	if(c=='H') return 3;
	if(c=='S') return 4;
	return 0;
}
inline char out(int c){//数字转字符
	if(c==1) return 'C';
	if(c==2) return 'D';
	if(c==3) return 'H';
	if(c==4) return 'S';
	return 0;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;){
		cin>>n>>c;k=0;int w=turn(c);
		for(int i=1;i<=4;++i) a[i].clear();//多测不清空，爆零两行泪
		for(int i=1;i<=2*n;++i){
			cin>>s;
			a[turn(s[1])].push_back(s[0]-'0');
		}
		for(int i=1;i<=4;++i)
			if(i!=w)//非王牌之间配对
				for(int j=0;j<(int)a[i].size()-1;j+=2){
					if(a[i][j]>a[i][j+1]) std::swap(a[i][j],a[i][j+1]);
					b[++k]=A{a[i][j],i,a[i][j+1],i};//小前大后
				}
		if(a[w].size()<(a[1].size()%2+a[2].size()%2+a[3].size()%2+a[4].size()%2-a[w].size()%2)){cout<<"IMPOSSIBLE\n";continue;}//判断王牌是否能匹配适配牌
		int p=a[w].size()-1;
		for(int i=1;i<=4;++i)//匹配失配牌
			if(i!=w&&a[i].size()%2){
				b[++k]=A{a[i][a[i].size()-1],i,a[w][p],w};
				--p;
			}
		for(int i=0;i<p;i+=2){//王牌之间配对
			if(a[w][i]>a[w][i+1]) std::swap(a[w][i],a[w][i+1]);
			b[++k]=A{a[w][i],w,a[w][i+1],w};
		}
		for(int i=1;i<=k;++i) cout<<b[i].a<<out(b[i].b)<<' '<<b[i].c<<out(b[i].d)<<'\n';
	}
	return 0;
}
```

---

## 作者：M1saka16I72 (赞：0)

# [CF1932D Card Games](https://codeforces.com/problemset/problem/1932/D) 题解

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-CF1932D.html)

## 思路
赛时没想出来贪心，于是写了爆搜但一直 WA，赛后发现是 dfs 函数忘记回溯了。

时间复杂度看起来是假的，但是跑得很快，推测是一堆卡牌里面能够进行匹配的数量实际上并没有那么多，实测最慢的点才 15ms，提交记录：[link](https://www.luogu.com.cn/record/147916030)

爆搜的方法就是先用 $(2n)^2$ 的时间预处理每两张牌是否能够匹配（匹配条件即两张牌中有且只有一张能赢过对方），然后再从第一张牌开始搜：对于每一张牌枚举和它匹配的另一张牌，标记之后接着搜下一张，搜不到就回溯继续搜，终止条件就是搜到第 $2n$ 张牌时 `return 1` 以及无解时 `return 0`。

## 代码
```cpp
constexpr int N = 40;

char trump;
int n;

struct card{
	char suit;int rank;
	inline void print(){cout<<rank<<suit;}
}c[N];

inline int win(card a,card b){	//a能否赢过b
	if(a.suit==b.suit)	return (a.rank>b.rank)?1:0;
	else if(a.suit==trump)	return 1;
	else return 0;
}

bool vis[N],leg[N][N];	//leg代表是否合法，vis代表是否被搜到过
int with[N];	//with[i]代表第i张牌被匹配的牌

bool dfs(int now){
	if(now==n*2)	return 1;	//有解
	if(vis[now])	return dfs(now+1);	//这张牌已经被匹配过了
	for(int i=1;i<=n*2;i++){
		if(leg[now][i] && !vis[i]){
			with[now] = i;
			vis[now] = vis[i] = 1;
			if(dfs(now+1))	return 1;	//搜索下一张牌
			with[now] = 0;	//一定记得回溯
			vis[i] = 0;
		}
	}
	vis[now] = 0;
	return 0;	//无解
}

void solve(){
	reset(with,0);reset(vis,0);
	cin>>n;
	cin>>trump;
	for(int i=1;i<=n*2;i++){
		cin>>c[i].rank>>c[i].suit;
	}
	for(int i=1;i<=n*2;i++){	//预处理，实际上放在搜索函数里判断也行
		bool have = 0;
		for(int j=1;j<=n*2;j++){
			if(i==j)	leg[i][j] = 0;
			else{
				if(win(c[i],c[j])+win(c[j],c[i])==1){
					leg[i][j] = 1;
					have = 1;
				}
				else leg[i][j] = 0;
			}
		}
		if(!have){cout<<"IMPOSSIBLE\n";return;}
	}
	if(!dfs(1))	cout<<"IMPOSSIBLE\n";	//无解
	else{
		for(int i=1;i<=n*2;i++){	//输出答案，记得能赢的那一张放在后面输出
			if(with[i]==0)	continue;
			int p2 = i,p1 = with[i];
			if(!win(c[i],c[with[i]]))	swap(p1,p2);
			c[p1].print();cout<<" ";
			c[p2].print();cout<<"\n";
		}
	}
}
```

---

## 作者：I_will_AKIOI (赞：0)

很棒的模拟题，赛时一遍过。

题意：有 $2n$ 张扑克牌，每张牌都有点数和花色。若两张牌花色相同，则点数大的牌大。若其中一张牌的花色为王牌，则王牌更大。否则无法比较。

每次一方出一张牌，另一方要出比他大的牌。现在给你一堆牌，问你存不存在这 $n$ 个游戏回合。

为了使游戏的顺序尽可能的存在，我们先考虑将**不是王牌且花色相同**的牌相互抵消，最后每种牌最多只会剩下一张牌，然后用王牌抵消。接着用王牌跟剩下的牌相互抵消。这里若王牌不够多，则无解。最后有可能会剩下一些王牌，还需要再抵消一次。

注意输出时小的牌放在大的牌前面，不要用 ```memset```，非常容易 TLE。

```
#include<bits/stdc++.h>
using namespace std;
int t,n;
char k;
string ans;
vector<int>v[4];
map<char,int>f;
map<int,char>g;
int main()
{
  ios::sync_with_stdio(0);
  f['C']=0,f['D']=1,f['H']=2,f['S']=3;
  g[0]='C',g[1]='D',g[2]='H',g[3]='S';
  //记录数字对应的牌的编号
  cin>>t;
  while(t--)
  {
  	char x,y;
  	int flag=1;
  	ans="";
  	for(int i=0;i<4;i++) v[i].clear();
	cin>>n>>k;//k表示王牌
	n*=2;
	for(int i=1;i<=n;i++)
	{
	  cin>>x>>y;
	  v[f[y]].push_back(x-'0');
	}
	for(int i=0;i<4;i++) sort(v[i].begin(),v[i].end());
	for(int i=0;i<4;i++)//先抵消花色相同的牌
	{
	  if(g[i]==k) continue;//王牌则跳过
	  while(v[i].size()>1)
	  {
	    ans+=char(v[i][v[i].size()-2]+'0');
	  	ans+=g[i];
		ans+=' ';
		ans+=char(v[i][v[i].size()-1]+'0');
		ans+=g[i];
		ans+='\n';
	  	v[i].pop_back();
	  	v[i].pop_back();
	  }
	}
	for(int i=0;i<4;i++)//用王牌和剩下的牌抵消
	{
	  if(g[i]==k) continue;
	  if(v[i].size()==1)
	  {
	  	if(v[f[k]].size()==0)
	  	{
	  	  cout<<"IMPOSSIBLE\n";
		  flag=0;
		  break;
		}
		ans+=char(v[i][v[i].size()-1]+'0');
		ans+=g[i];
		ans+=" ";
		ans+=char(v[f[k]][v[f[k]].size()-1]+'0');
		ans+=k;
		ans+='\n';
		v[i].pop_back();
	  	v[f[k]].pop_back();
	  }
	}
	if(!flag) continue;
	while(v[f[k]].size()>1)//还有多的王牌，抵消掉
	{
	  ans+=char(v[f[k]][v[f[k]].size()-2]+'0');
	  ans+=k;
	  ans+=" ";
	  ans+=char(v[f[k]][v[f[k]].size()-1]+'0');
	  ans+=k;
	  ans+="\n";
	  v[f[k]].pop_back();
	  v[f[k]].pop_back();
	}
	cout<<ans;
  }
  return 0;
}
```

---

## 作者：No_Rest (赞：0)

## 思路

大模拟。会桥牌，感觉良好。

我们可以贪心地将非将牌花色全部一对对出掉，而剩下的牌就只能靠将牌将吃了。这时候可以判将牌花色张数是否比剩下的牌少，如果少的话就无解了。

算出将吃所需的将牌后就可以开始输出解法了。

我们先进行一对对出掉的贪心步骤。为了确保两张牌是同一个花色，需要对原来的字符串数组进行排序。发现 ASCII 码正好 $\texttt C < \texttt D < \texttt H < \texttt S$，于是可以将原字符串翻转然后 sort。输出很简单，但要注意将牌所出张数与其他花色不同。

然后是将吃。令 $lst$ 为在字符串数组中最后一张将牌花色的下标。那么我们可以再计一个 $tot$，每次将吃时将牌就输出 $lst - tot$ 下标的牌，然后 $tot \gets tot + 1$。

然后就没了。时间复杂度 $\mathcal O(Tn)$。

调得很痛苦。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 2e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), n, a[maxn], ans, cntc, cntd, cnth, cnts, cnt, cnttr, tot;
char tr;
string s[maxn], st[maxn];
void solve(){
	n = read(), cntc = cntd = cnth = cnts = cnt = cnttr = tot = 0;
	cin >> tr;
	for(ll i = 1; i <= 2 * n; ++i){
		cin >> s[i];
		if(s[i][1] == tr) cnttr++;//计算将牌张数及各花色张数
		if(s[i][1] == 'C') cntc++;
		else if(s[i][1] == 'D') cntd++;
		else if(s[i][1] == 'H') cnth++;
		else cnts++;
		st[i] = "";//单拎一个字符串数组记录翻转后的牌
		st[i] = st[i] + s[i][1];
		st[i] = st[i] + s[i][0];
	}
	ll lst;
	if('C' != tr) cnt += cntc & 1;//算需要多少张将牌将吃，顺便计算 lst
	else lst = cntc;
	if('D' != tr) cnt += cntd & 1;
	else lst = cntc + cntd;
	if('H' != tr) cnt += cnth & 1;
	else lst = cntc + cntd + cnth;
	if('S' != tr) cnt += cnts & 1;
	else lst = cntc + cntd + cnth + cnts;
	if(cnttr < cnt){//若需要的将牌数比实际将牌数多，那么无解
		puts("IMPOSSIBLE");
		return;
	}
	sort(st + 1, st + 2 * n + 1);//排序
	if('C' != tr){//贪心地一对对出
		for(ll i = 1; i <= cntc - (cntc & 1); i += 2) cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	} else for(ll i = 1; i <= cntc - cnt; i += 2) cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	if('D' != tr){
		for(ll i = cntc + 1; i <= cntc + cntd - (cntd & 1); i += 2)	cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	} else for(ll i = cntc + 1; i <= cntc + cntd - cnt; i += 2) cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	if('H' != tr){
		for(ll i = cntc + cntd + 1; i <= cntc + cntd + cnth - (cnth & 1); i += 2)	cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	} else for(ll i = cntc + cntd + 1; i <= cntc + cntd + cnth - cnt; i += 2) cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	if('S' != tr){
		for(ll i = cntc + cntd + cnth + 1; i <= cntc + cntd + cnth + cnts - (cnts & 1); i += 2) cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	} else for(ll i = cntc + cntd + cnth + 1; i <= cntc + cntd + cnth + cnts - cnt; i += 2) cout << st[i][1] << st[i][0] << " " << st[i + 1][1] << st[i + 1][0] << endl;
	if(cntc & 1 && 'C' != tr) cout << st[cntc][1] << st[cntc][0] << ' ' << st[lst - tot][1] << st[lst - tot][0] << endl, tot++;//处理将吃
	if(cntd & 1 && 'D' != tr) cout << st[cntc + cntd][1] << st[cntc + cntd][0] << ' ' << st[lst - tot][1] << st[lst - tot][0] << endl, tot++;
	if(cnth & 1 && 'H' != tr) cout << st[cntc + cntd + cnth][1] << st[cntc + cntd + cnth][0] << ' ' << st[lst - tot][1] << st[lst - tot][0] << endl, tot++;
	if(cnts & 1 && 'S' != tr) cout << st[cntc + cntd + cnth + cnts][1] << st[cntc + cntd + cnth + cnts][0] << ' ' << st[lst - tot][1] << st[lst - tot][0] << endl, tot++;
}
int main(){	
	for(; t; --t) solve(); 
    return 0;
}
```

---

