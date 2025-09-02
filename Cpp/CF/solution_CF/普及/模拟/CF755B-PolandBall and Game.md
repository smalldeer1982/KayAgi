# PolandBall and Game

## 题目描述

两个人玩一个游戏 他们轮流说单词  
每一个人只能说出自己会的单词 并且任何一个在之前被说过(被自己或对方说过)的单词不能被再说一次  

最后无话可说(所有会的单词都被说过)的人负  
问先手是否能获胜

## 样例 #1

### 输入

```
5 1
polandball
is
a
cool
character
nope
```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 2
kremowka
wadowicka
kremowka
wiedenska
```

### 输出

```
YES```

## 样例 #3

### 输入

```
1 2
a
a
b
```

### 输出

```
NO```

# 题解

## 作者：I_like_magic (赞：8)

这题其实不难。

两人最佳的方案就是先说对方会的词。

不难证明，设先手会说 $n$ 个单词，后手会说 $m$ 个单词，

若 $n>m$，则先手胜，若 $n<m$，则后手胜。

那如果 $n=m$ 呢？

假设两人都会说的单词数为 $k$，

那么一番推理发现，当两人说了 $k-1$ 次，就没有两人都会的词了，可以回到之前的情况考虑。

所以，如果 $k$ 为奇数，$k-1$ 就是偶数，说完了之后两人词汇量相等，则先手胜，反之，则后手胜。

AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
string a;
map<string,bool>f; //用于统计都会的
signed main() {
	scanf("%d%d", &n, &m);
	if(n > m) {
		puts("YES");
		exit(0);
	}else if(n < m) {
		puts("NO");
		exit(0);
	} //两种情况特殊判断
	for(int i = 1 ; i <= n ; i++){
		cin >> a;
		f[a] = 1; //统计先手会的词
	}
	for(int i = 1 ; i <= m ; i++){
		cin >> a;
		if(f[a]) k++; //统计都会的词
	}
	if(k & 1) puts("YES");
	else puts("NO"); //判断
	return 0; //完美收尾
}
```

---

## 作者：AzureMist (赞：7)

对于这两个人而言，最优策略就是先说对方会的单词。

如果A的词汇量比B的词汇量大，那么肯定是A赢，同理，如果B的词汇量比A的词汇量大，那么肯定是B赢。可是，如果两个人的词汇量相等，应该怎么办呢？

没错，当然是看两个人都会的单词数量。我们可以设A会但是B不会的单词数量为 $n$，B会但是A不会的单词数量为 $m$，两个人都会的单词数为 $k$.则如果 $k$ 为奇数，那么两个人对喷把 $k$ 用光之后，B就成为了先手，如果 $k$ 为偶数，那么两个人对喷把 $k$ 用光之后，A就成为了先手。因为 $k$ 被用完之后，两人剩余的词汇量是相等的，所以这时谁先手谁就输了。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
set<string> word;
string str;
int main()
{
	cin>>n>>m;
	k=0;
	for(int i=0;i<=n-1;i++)
	{
		cin>>str;
		word.insert(str);
	}
	for(int i=0;i<=m-1;i++)
	{
		cin>>str;
		if(word.count(str)>0) k++;
	}
	n-=k;
	m-=k;
	k%=2;
	n+=k;
	if(n>m) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```
注意这个地方：
```cpp
n-=k;
m-=k;
k%=2;
n+=k;
```
其中的：
```cpp
n-=k;
m-=k;
```
更新了A和B的词汇量；

那么这个怎么解释呢？
```cpp
k%=2;
n+=k;
```
如果 $k$ 是奇数，那么 $n$ 会加上1，然后就是A赢；如果 $k$ 是偶数，那么 $n$ 的值不会改变，然后执行 else 语句，此时是B赢。

---

## 作者：lianchanghua (赞：7)

个人认为，这是一道“贪心+博弈论”的题。

最优策略必然是优先说掉所有公共单词，然后再说非公共单词。

设公共单词的数量为 $x$。

- 若 $x$ 为奇数，那么最后一个说出公共单词的是先手，此时若 $(n\ge m)$ 则先手胜。

- 若 $x$ 为偶数，那么最后一个说出公共单词的是后手，此时若 $(n > m)$ 则先手胜。

就以上这些，想通之后就十分简单。

AC Code:
```cpp
#include<bits/stdc++.h>//万能头 
#define int long long//保险起见 
using namespace std;
map<string,int> p;//记录公共单词 
int n,m;
signed main(){
    ios::sync_with_stdio(false);//加个速 
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	string s;
    	cin>>s;
		p[s]++;
	}//第一个人的单词数 
    for(int i=1;i<=m;i++){
    	string s;
    	cin>>s;
		p[s]++;
	}//第二个人的单词数 
    int x=0;
    for(map<string,int>::iterator it=p.begin();it!=p.end();it++){
    	x+=(it->second==2);
	}//装波小B(我才不会告诉你我刚学会呢！) 
    if(x%2){//你如果想装B的话，也可以用x&1 
    	if(n>=m)		cout<<"YES\n";
		else			cout<<"NO\n";
	}
    else{
    	if(n>m)		cout<<"YES\n";
		else		cout<<"NO\n";
	}
    return 0;//华丽结束
}
```


---

## 作者：installb (赞：3)

由于每一个人都很聪明 所以轮到自己的时候一定是先说对面会的单词  这样相当于可以尽可能减少对面在接下来的选择  

首先如果一个人词汇量大于另一个人 那么这个人必胜  
~~证明:~~  
都会的单词先会被说完 去掉这些后该词汇量大的人词汇量还是大 每一轮每方说掉一个自己的单词 总有一轮词汇量大的人说完后 另一个人就已经用完所有词汇了  

词汇量两人相等的时候 看有多少个词汇两个人都知道  
**如果是奇数个** 先手会比后手多说一个都会的词 先手会但是无法说出的词汇比后手少一个 先手必胜  
**如果是偶数个** 先手和后手说的数量同样 由于先手先说 先手和后手都说完以后轮到的是先手 先手必输  

此题完结  
**code:**  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
using namespace std;
typedef long long LL;

LL n,m,w = 0;
string s;
map <string,LL> mp;
 
int main(){
	cin >> n >> m;
	for(LL i = 0;i < n;i ++){
		cin >> s;
		mp.insert(make_pair(s,1));
	}
	for(LL i = 0;i < m;i ++){
		cin >> s;
		if(mp.find(s) != mp.end()) w ++; // 统计两人都会的词汇数
	}
	if(n > m){ cout << "YES" << endl; return 0; } // 先手词汇量大
	if(n < m){ cout << "NO" << endl; return 0; } // 后手词汇量大
	// n == m
    // 词汇量一样大 看共有词汇
	if(w & 1){ cout << "YES" << endl; return 0; }
	cout << "NO" << endl; return 0;
	return 0;
}
```

---

## 作者：wangyi_c (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF755B)

[原题地址](https://codeforces.com/problemset/problem/755/B)

## 1.题目大意

两个人玩说单词游戏，有两个人的词库，可以从中任意说单词，但是**别人说过的自己就不能再说，且不能说自己说过的单词**，问先手能否获胜。

## 2.思路讲解

两个人都聪明绝顶，肯定会先说对方也会的单词，来消耗对方的储备。

首先，可以获得两个很~~明显~~的结论：

- 当先手的词汇数比后手多时，则先手必胜。

- 反之，当后手的词汇数比先手多时，则后手必胜。

证明如下：两个人会说的单词总会被说完，设先手有 $a$ 的储备，后手有 $b$ 的储备，两个人都会的单词数目为 $k$。说完都会的单词后，先手还有 $a-k$ 的单词，后手还有 $b-k$ 的单词，最后只能消耗自己会的单词了。明显的，$a-k$ 与 $b-k$ 的大小取决于 $a$ 和 $b$ 的大小（ $k$ 肯定是正整数）。则原来的单词储备多的那一方必胜。

如果 $a$ 和 $b$ 的大小一样，则又可以分为两个情况：

- 当 $k$ 为奇数的时候，先手能比后手多说一个都会的单词，所以先手必胜。

- 当 $k$ 为偶数的时候，后手能比先手多说一个都会的单词，所以后手必胜。

思路都明白了，代码就很好写了。

## 3.AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
string str;
set <string> s; //单词库
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>str;
		s.insert(str);
	}
	int cnt=0;
	for(int i=1;i<=m;i++){
		cin>>str;
		if(s.count(str)){
			cnt++;//寻找共同会的单词
		}
	}
	if(n>m){//先手原本储备就比后手多
		cout<<"YES";
	}
	else if(n<m) cout<<"NO";//后手原本储备就比先手多
	else{
		if(cnt%2==1){//共同会的为奇数
			cout<<"YES";
		}
		else{//共同会的为偶数
			cout<<"NO";
		}
	}
	return 0;
}
```

谢谢观看。

_THE END_

By [wangyi_c](https://www.luogu.com.cn/user/560044)


---

## 作者：_ouhsnaijgnat_ (赞：1)

## 思路

这道题是道贪心的题目，贪心的策略就是先把两个人都会的单词全说了，再说对方不会的，这样即是最优。

我们用两层循环找出来相同的单词，时间复杂度为 $O(n\times m)$。

当相同的单词是奇数时，先手能说对方不会的 $+$ 相同的单词数 $\div2$，如果相同的单词数为奇数，那么先手就能多说一个。

当后手时也是如此，但并不需要 $+1$，因为不管怎样后手都不可能比先手多说一个。

这样就算出来能说多少个单词，再比个大小。

代码奉上，很丑勿喷。

## 代码

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;
int al,bl,xt;//xt表示相同的个数 
string a[1005],b[1005];
int main(){
	cin>>al>>bl;
	for(int i=1;i<=al;i++)
		cin>>a[i];
	for(int i=1;i<=bl;i++)
		cin>>b[i];
	for(int i=1;i<=al;i++){
		for(int j=1;j<=bl;j++){
			if(a[i]==b[j])xt++;//找出相同单词的个数 
		}
	}
	al=(al-xt)+(xt/2+(xt%2));
	//先手要将会的单词减去相同的单词，再加上两个人首先都说相同的单词时先手能说多少个，这个mod 2表示如果相同单词的数量是单数，则先手能多说一个 
	bl=(bl-xt)+(xt/2);//同上，此为后手 
	if(al<=bl)cout<<"NO";//如果先手能说的单词小于等于后手，那就输，否则赢。 
	else cout<<"YES";//
	return 0;
}
```


---

## 作者：qhztz (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF755B)
## 思路：
由于每一个人都很聪明 所以轮到自己的时候一定是先说对面会的单词 这样相当于可以尽可能减少对面在接下来的选择

首先如果一个人词汇量大于另一个人 那么这个人必胜

词汇量两人相等的时候 看有多少个词汇两个人都知道。

**如果是奇数个**：

先手会比后手多说一个都会的词 先手会但是无法说出的词汇比后手少一个 **先手必胜**。

**如果是偶数个**：

先手和后手说的数量同样 由于先手先说 先手和后手都说完以后轮到的是先手 **先手必输**。

在第一个例子中，PolandBall 知道更多的单词所以毫不费力地获胜。

在第二个例子中，如果 PolandBall 先说 kremowka ，那么 EnemyBall 就不能再使用这个词了。 EnemyBall 只能说 wiedenska 。PolandBall 再说 wadowicka 就胜利了。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt;
string s;
map<string,int>mp;//用map记录共有单词数
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>s;
        mp[s]++;
    }
    for(int i=1;i<=m;++i){
        cin>>s;
        if(mp[s]==1) cnt++;//统计两人都会的词汇数
        mp[s]++;
    }
    if(cnt%2==1)
        if(n-cnt>=m-cnt) cout<<"YES";//判断奇偶
        else cout<<"NO";
    else
        if(n-cnt>m-cnt) cout<<"YES";//判断单词量
        else cout<<"NO";
}
```
拜拜qwq

---

## 作者：钺Programmer (赞：1)

### 题目大意：

两个人在玩单词游戏。每一回合一个人说一个单词，说过的词不能再说。谁说不出来了谁就输了。

### 题目思路：

我相信大家都玩过飞花令吧。我们通常都是先说广为人知的诗句，这样其他人就不能说了。所以这道题很简单，找出两个人都会说的词，然后做以下判断。

>如果重复的词有奇数个，

>>如果先手知道的词多于或等于后手，先手赢。

>>反之，后手赢。

>如果重复的词有偶数个，

>>如果先手知道的词严格多余后手，先手赢。

>>反之，后手赢。

### AC代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt;
string s;
map<string,int>mp;
int main(){
    cin>>n>>m;
    for(register int i=1;i<=n;++i){
        cin>>s;
        ++mp[s];
    }
    for(register int i=1;i<=m;++i){
        cin>>s;
        if(mp[s]==1){
            ++cnt;
        }
        ++mp[s];
    }
    if(cnt%2==1){
        if(n-cnt>=m-cnt){
            cout<<"YES";
        }else{
            cout<<"NO";
        }
    }else{
        if(n-cnt>m-cnt){
            cout<<"YES";
        }else{
            cout<<"NO";
        }
    }
    return 0;
}
```

---

## 作者：ruruo (赞：0)

首先 如果一个人的词汇量比另一个人大 那词汇量大的人一定赢

这道题的难点就是在于如何处理词汇量相等的情况。我们假设 $cnt$ 是两个人都会的词语数，

若 $cnt$ 为偶数，那就是你说一个我说一个，说完后先手还是先手，但又因为双方只有自己会的词语数相等，所以先手必输；

反之，若 $cnt$ 为偶数，那先手会多说一个，说完后手就会变成先手，但又因为双方只有自己会的词语数相等，所以先手必赢。

AC Code:


```cpp
#include<iostream>
using namespace std;

int main() {
    string s1[1005], s2[1005];
    int n, m, cnt = 0;
    cin >> n >> m;
    if(n > m){
        cout << "YES";
    }else if(n < m){
        cout << "NO";
    }else{
        for(int i = 1; i <= n; i++){
            cin >> s1[i];
        }
        for(int i = 1; i <= m; i++){
            cin >> s2[i];
            for(int j = 1; j <= n; j++){
                if(s1[j] == s2[i]) cnt++;
            }
        }
        if(cnt % 2 == 0){
            cout << "NO";
        }else{
            cout << "YES";
        }
    }
    return 0;
}
```

---

## 作者：Together_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF755B)

## 题目大意：

给定先者会的 $n$ 个单词，和后者会的 $m$ 个单词，第 $1$ 次由先者说一个单词，第 $2$ 次由后者说一个单词，第 $3$ 次又由先者说，第 $n$ 次时，若 $n$ 为奇数，则由先者说，否则由后者说，每次说的必须是自己和别人都没说过的单词，当先者或后者中有一个满足不了上述条件，游戏结束，对方获胜。现在给出先者会的单词和后者会的单词，让你求先者能否获胜。

## 思路：

- #### 对于这两个人而言，最优策略是什么？

他们的最优策略是**先说对方会的单词**，所以如果先者的词汇量大于后者，那么必然先者胜，如果后者的词汇量大于先者，那么必然后者胜。

#### 所以我们只要考虑两人词汇量相同的情况

- #### 如果两人的词汇量相同，满足什么条件先者会胜？

我们假设两人都会的单词有 $x$ 个，那么如果 $x$ 是奇数，则从后者开始说我会你不会的这种单词，由于这种我会你不会的单词在先者中的数量和在后者中的数量是相等的，所以此时先者就胜了。

## 代码：

```cpp
#include <bits/stdc++.h>
 
using namespace std;

int n,m,w = 0;
string s;
map <string,int> mp;
 
int main(){
	cin>>n>>m;
	for(int i = 0;i < n;i ++){
		cin >> s;
		mp[s] = 1;
	}
	for(int i = 0;i < m;i ++){
		cin >> s;
		if(mp[s] == 1) w++;
	}
	if(n > m)
	{ 
		cout<<"YES"; 
		return 0; 
	}
	else if(n < m)
	{ 
		cout<<"NO"; 
		return 0; 
	}
	if(w % 1 == 1)
	{ 
		cout<<"YES"; 
		return 0; 
	}
	cout<<"NO";
	return 0;
}
```


---

## 作者：xiezihanAKIOI (赞：0)

题解区看了一下各位大佬的代码。就目前为止，我的代码好像是最短的。

首先，因为两个人都很聪明，所以他们一定会先说双方都有的单词。那么，就会出现两种情况。

情况一：双方都会的单词有奇数个，那么两人说双方都会的单词时，后手的那个人肯定先说完。那么我们就可以理解为第一个人赚了一个单词。那么我们直接将 $n+1$ 后与 $m$ 作比较即可。

情况二：双方都会的单词有偶数个。那么先说的那个人先说完。双方都不赚。直接将 $n$ 和 $m$ 比较即可。

代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

int cnt, n, m;
string s;
map <string, int> ma;

signed main () {
	cin >> n >> m;
	for (int i = 1 ; i <= n ; i++) {
		cin >> s;
		ma[s] = 1;
	}
	for (int i = 1 ; i <= m ; i++) {
		cin >> s;
		if (ma[s]) {
			cnt++;
		}
	}
	if (cnt % 2 == 1) {
		n++;
	}
	cout << (n > m ? "YES" : "NO");
	return 0;
}
```


---

## 作者：wangkangyou (赞：0)

这应该是(个人认为，有误请私信指出，不胜感激)一道类似于博弈论的入门题目。\
题目翻译非常简短，不用多说了。直接举栗(有三种情况):
1. 先手(以下简称 $A$ )的词汇量比后手(以下简称 $B$ )多，这时就无须考虑任何方案，$A$ 的无论接下来读哪一个词都可以一个一个耗死 $B$，于是输入时就加判断直接输出 `YES` ;
2. 如果 $B$ 的词汇量比 $A$ 大，那这次占据压倒性有事的就是 $B$ ,无论 $A$ 用什么方法去读，$B$ 采取的必胜策略就是一个个去跟TA耗，最终输出 `NO` ;
3. 如果他俩的词汇量相等，那谁赢谁输就不是平时用不用功的问题了，而是两人背的词有多少相同的了。举个栗子，
$\color{red} 1 \color{blue} 2 \color{red} 3$
,为他们都会的单词序号，红色的代表是 $A$ 读的，蓝色的则是 $B$ 读的，从颜色上可以看出，最后一个都会的单词是 $A$ 读的，此时还没读的单词都是一人会一人不会的，此时谁读谁输，于是问题就变成了都会读的单词数判奇偶问题了。

其他的部分容各位伟大的神牛们自己推敲推敲，上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int sum=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) sum=(sum<<3)+(sum<<1)+(ch^48);
	return sum*f;
}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar('0'+x%10);
	return;
}
const int inf=1e10;
const int N=1e6+10;
string str1[N], str2[N];
set <string> se;//我在这里用了一个set来统计都会的个数，听说有神犇用哈希的 
signed main(){
	int n = read (), m = read (), s = 0;
	if (n > m){
		puts ("YES");
		return 0;
	}else if (n < m){
		puts ("NO");
		return 0;
	}
	for (int i = 1; i <= n; ++ i) cin >> str1[i], se.insert (str1[i]);
	for (int i = 1; i <= m; ++ i){
		cin >> str2[i];
		if (se.count (str2[i])) s ++; 
	}
	if (s % 2 == 1) puts ("YES");
	else puts ("NO");
	return 0;
} 

```

---

## 作者：WinterRain208 (赞：0)

## CF755B 【PolandBall and Game】

#### 题意：

两个人玩游戏，他们各知道一些单词，每轮他们分别说出自己会的一个单词，不能重复，求先手是否有必胜策略。

两个人都非常聪明。

个人认为原题目中


Note that one Ball cannot know a word more than once (strings are unique), but some words can be known by both players.


是非常重要的，因为这说明同一个人会的单词输入中不会重复。

#### 分析：

两个人都会先说出对方知道自己也知道的单词，这样可以减少对方的词汇量。

首先先手词汇量不能少于后手。

否则在两人说完共同掌握的词汇后，先手词汇量就会占劣势。

举例证明：

先手词汇量$6$，后手$7$，设两人共同掌握四个单词。

则两回合后，先手还剩两个，后手还剩三个，此时轮到先手，必败。

设两人共同掌握三个单词。

一个半会合后，先手还剩三个单词，后手还剩四个，此时轮到后手，必败。

其次，当两人的总词汇量相等时，考虑共同掌握的单词的奇偶。

举例证明：

先手后手掌握八个单词。

共同掌握$4$个单词。

两回合后后两人剩余词汇相等，轮到先手，必败。

共同掌握$3$个单词。

（还是按奇偶分类举例）

一个半会合后两人剩余词汇相等，轮到后手，必胜。

看懂了吗？

这其实是一个先后手转移的过程，若干会合后，两人词汇量必定相等且没有重复。

这是胜负取决于这时轮到先手还是后手，显然，轮到谁谁输。

###### 本段总结

设先手会$m$个单词，后手$n$个，共同的有$k$个。

先手胜：

$m>n$||$m=n$&&$k%2==1$。

#### 代码部分 丑陋的代码

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e5+5;

int n,m,tot=0;
string a[N],x;
map < string , int > mp;
int main(){
	scanf("%d%d",&n,&m);
	F(i,1,n)
		cin>>a[i];
	F(i,1,m){
		cin>>x;
		mp[x]=1;
	}
	F(i,1,n)
		tot+=mp[a[i]];
	puts((m>n||(m==n&&tot%2==0))?"NO":"YES");
    return 0;
}

```

注释就不写了，关于字符串的储存我们使用了$map$。最后判定并输出。

$wtrl$。


---

## 作者：开始新的记忆 (赞：0)

用map记录共有单词数，如果先手会的多或者共有词汇刚好有奇数个且两个人会的一样多，那么先手胜，反之则后手胜

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<map>
using namespace std;

map <string , bool > visited;

int main()
{   int n,m,ans=0;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        string a;
        cin>>a;
        visited[a]=1;
    }
    for(int i=1;i<=m;++i)
    {
        string a;
        cin>>a;
        if(visited[a])
            ans++;
        visited[a]=1;
    }
    if(n>m || (n==m && ans%2==1))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
```


---

## 作者：Zijun_Xu (赞：0)

## 先统计都会的词(strcmp...)记作  **C**
0. 我们把选手能说的词记为有效单词。

1. 先手和后手都是聪明的，都要把自己会的单词尽量说完，因此对于每个都会的单词，必然会一个先手抢了（后手有效单词数-1），然后下一个后手抢了（先手有效单词数-1），以此类推。故**C**为奇数时，先手多抢后手一个单词，**C**偶数没有影响。


2. **YES** or **NO**只是由   **A=先手有效单词数 〇 B=后手有效单词数（圈内填>或<=）** 即为 **A-B** 的 **+/-** 决定。



3. 注意：\
   3.1 如果两人有效词数相等，则最后后手说完先手就输了。\
   3.2 两人有效单词数同时减少等量可以看作没有减少。\


### 贴上AC代码

````
#include<bits/stdc++.h>
using namespace std;
char a[2002][522];
int main()
{
    int n,m;
    bool bo=0;
    scanf("%d%d",&n,&m);
    int p=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",a[i]);
    }
    for(int i=n+1;i<=n+m;i++)
    {
        scanf("%s",a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=n+1;j<=n+m;j++)
        {
            if(strcmp(a[i],a[j])==0)
            {
                p++;//比较字符串是否相等
            }
        }
    }
    m-=p%2;
    if(n>m)
    {
        printf("YES");//先手赢
    }
    else
    {
        printf("NO");
    }
    return 0;
}
````

---

