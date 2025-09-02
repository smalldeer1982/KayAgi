# [AGC063A] Mex Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc063/tasks/agc063_a

`A`, `B` からなる長さ $ N+1 $ の文字列 $ S\ =\ S_0\cdots\ S_N $ が与えられます． 各 $ k=1,\ \ldots,\ N $ に対して次の問題を解いてください：

> Alice と Bob が集合 $ X $ を使ってゲームをします．$ X $ ははじめ空集合で，$ t=1,\ldots,\ k $ の順に次の行動を行います．
> 
> - $ t $ が奇数ならば，Alice が非負整数 $ x $ を選び，$ X $ を $ X\cup\ \{x\} $ に置き換える．
> - $ t $ が偶数ならば，Bob が非負整数 $ x $ を選び，$ X $ を $ X\cup\ \{x\} $ に置き換える．
>  
> $ k $ 回すべての行動が終わった時点での $ \mathrm{mex}(X) $ を $ x $ とするとき，文字 $ S_x $ が `A` ならば Alice が，$ S_x $ が `B` ならば Bob が勝者となります．集合 $ X $ の要素数は $ k $ 以下であるため，$ x\ =\ \mathrm{mex}(X)\ \leq\ k $ が成り立つ（したがって文字 $ S_x $ が存在する）ことに注意してください．
> 
> 両者が最適に行動した場合の勝者の名前を出力してください．

   $ \mathrm{mex}(X) $ とは？ 非負整数からなる有限集合 $ X $ に対し，$ x\notin\ X $ を満たす最小の非負整数 $ x $ を $ \mathrm{mex}(X) $ と定義します．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ S $ は `A`, `B` からなる長さ $ N+1 $ の文字列である．
 
### Sample Explanation 1

$ k=1 $ とした場合のゲームの進行例の一例を次に示します． - Alice が $ x=10 $ を選ぶ． - $ \mathrm{mex}(X)=\mathrm{mex}(\lbrace\ 10\rbrace)\ =\ 0 $ であり，$ S_0 $ は `A` なので，Alice が勝利する． $ k=2 $ とした場合のゲームの進行例の一例を次に示します． - Alice が $ x=2 $ を選ぶ． - Bob が $ x=0 $ を選ぶ． - $ \mathrm{mex}(X)=\mathrm{mex}(\lbrace\ 0,2\rbrace)\ =\ 1 $ であり，$ S_1 $ は `B` なので，Bob が勝利する．

## 样例 #1

### 输入

```
2
ABB```

### 输出

```
Alice
Bob```

## 样例 #2

### 输入

```
4
AAAAA```

### 输出

```
Alice
Alice
Alice
Alice```

## 样例 #3

### 输入

```
7
BBAABABA```

### 输出

```
Bob
Bob
Alice
Bob
Alice
Bob
Alice```

# 题解

## 作者：chinazhanghaoxun (赞：6)

## 题意

如题面翻译，这次的翻译还是嘎嘎给力的，感谢本次翻译者。
## 分析

由 mex 函数的定义可知，一个集合中的数绝不可能是这个集合的 mex。那么 Alice 就一定会选择第一个还没出现的 ```B``` 的下标加入这个 $X$ 集合，那样就让 Bob 获胜的可能性更小了。同理，Bob 也会选择第一个还没出现的 ```A``` 下标加入集合。那么这道题变成了就每一轮比较 ```A``` 和  ```B``` 出现的次数了，非常简单，如果 ```A``` 多，那么 Alice 获胜，否则 Bob 获胜，直接循环模拟即可。

注意，还有一种特殊情况，就是 $cnta=cntb$，这是也是 Alice 获胜，因为她是先手。
## 代码+注释

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int cnta,cntb;//分别统计A和B出现的次数 
string s;
int main(){
	cin>>n>>s;
	//使用三目运算符非常方便 
	(s[0]=='A') ? cnta++ : cntb++;
	for(int i=1;i<=n;i++){ //从1开始循环模拟 
		(s[i]=='A') ? cnta++ : cntb++;
		if(cnta>=cntb) puts("Alice"); //A更多 
		else  puts("Bob");
	} 
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：2)

## 题意

给定一个长度为 $(n+1)(1\le n\le 2\times 10^5)$ 的字符串 $s$。共 $n$ 轮游戏，第 $i$ 轮进行 $i$ 次操作，每轮均由 `Alice` 先，与 `Bob` 交替往集合 $X$ 中加入非负整数（一次加入即一次操作）。对于每一轮，记 $x=\mathrm{mex}(X)$，若 $s_x$ 为 $A$ 则 `Alice` 胜，反之 `Bob` 胜。对于每一轮，输出谁胜。

## 思路

容易发现，`Alice` 一定选 $s_i$ 为 $B$ 的 $i$，同样 `Bob` 一定选 $s_i$ 为 $A$ 的 $i$。

对于第 $i$ 轮，有 $\mathrm{mex}(X)\le i$，因此仅有 $s$ 的前 $i+1$ 位起到作用。记这其中字符 `A` 有 $cnta$ 个，字符 `B` 有 $cntb$ 个。当 $i$ 为偶数时，两人操作次数相同，此时若 $cnta>cntb$ 则必定剩下 `A`，即 `Alice` 胜；反之 `Bob` 胜。当 $i$ 为奇数时，`Alice` 能操作 $\frac{i+1}{2}$ 次，而 `Bob` 仅能操作 $\frac{i-1}{2}$ 次，因此只要 `A` 的个数超过一半，即 $cnta\ge cntb$ 时 `Alice` 胜，否则 `Bob` 胜。综上，当 $cnta\ge cntb$ 时 `Alice` 胜，否则 `Bob` 胜。

## 代码

```cpp
string s;
ll n;
void solve(){
	cin>>n>>s;
	ll cnta=0,cntb=0;
	for(int i=0;i<=n;i++){
		cnta+=(s[i]=='A');
		cntb+=(s[i]=='B');
		if(i==0)continue;
		if(cnta>=cntb)cout<<"Alice"<<endl;
		else cout<<"Bob"<<endl;
	}
	return;
}
```


---

## 作者：nahidaa (赞：1)

## [传送门](https://www.luogu.com.cn/problem/AT_agc063_a)
## 正文
通过题意，我们可以知道这是一道博弈论的题。

而后我们通过模拟，得出该题的最优方案如下：

我们取数要取与自己立场对立的数中的编号最小的数，打个比方就是 Alice 取编号最小的 B，Bob 取编号最小的 A。若剩余的序列中，第一个是 A，则 Alice 赢，反之 Bob 赢。

随后，得知了最优方案，则可以逐个进行模拟。

## 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ba[200005],bb[200005],bacnt,bbcnt,l,r;
string a;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    cin>>a;
    a=" "+a;
    n++;
    for(int i=1;i<=n;i++){
        if(a[i]=='A'){
            ba[++bacnt]=i;//记录A的出现位置、统计A的数量
        }
        else if(a[i]=='B'){
            bb[++bbcnt]=i;//记录B的出现位置、统计B的数量
        }
    }
    l=0,r=0;
    for(int i=1;i<n;i++){
        if(i%2==1){//Alice选
            if(r!=bbcnt)r++;//Alice选取还未被取的编号最小的B
            else{//如果所有的B都被取完，那么Alice之后必定全部获胜
                for(int h=i;h<n;h++)cout<<"Alice\n";
                return 0;
            }
        }
        else {//Bob选
            if(l!=bacnt)l++;//Bob选取还未被取的编号最小的A
            else{//如果所有的A都被取完，那么Bob之后必定全部获胜
                for(int h=i;h<n;h++)cout<<"Bob\n";
                return 0;
            }
        }
        if(max(ba[l],bb[r])==i){//出现将1—i全都取了，则要检测i+1位置
            if(a[i+1]=='A'){
                cout<<"Alice\n";//若i+1是A则Alice获胜，反之Bob获胜
            }
            else cout<<"Bob\n";
        }
        else{
            if(ba[l]<bb[r]){//若剩余的第一个数为A则Alice胜，反之Bob胜
                cout<<"Alice\n";
            }
            else cout<<"Bob\n";
        }
    }
    return 0;
}
/*

*/

---

## 作者：goIdie (赞：1)

## 思路
博弈论。

对 $mex$ 函数的解释大部分题解都给过了，这里不再赘述。

不难发现，每个在集合里的数都不可能成为 $mex$。那么我们简化一下题意，每人每次去除一个字母，如果剩下的字母下标最小的为 $A$ 则 Alice 胜，否则 Bob 胜。那么贪心策略就很简单了，为了使剩下的字母下标最小的为 $A$，Alice 会每次取出下标最小的 $B$。反之，Bob 则会每次取出下标最小的 $A$。再次简化题意，比较 $A$ 和 $B$ 的数量即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n,cnta,cntb;
signed main(){
    cin>>n>>s;
    if(s[0]=='A'){
        cnta++; 
    }
    else{
       cntb++; 
    }
    for(int i=1;i<=n;i++){
        if(s[i]=='A'){
           cnta++; 
        } 
        else{
          cntb++;  
        } 
        if(cnta>=cntb){
           cout<<"Alice"<<endl; 
        } 
        else{
            cout<<"Bob"<<endl; 
        }
    }
}
```

---

## 作者：pengbubu (赞：1)

## 题意
1. **$\operatorname{mex}$ 函数是什么**：$\operatorname{mex}$ 函数‌是指在集合中没有出现过的最小的非负整数。例如，$\operatorname{mex}({3,5})=0$，$\operatorname{mex}({0,1,2,3})=4$。
2. $\operatorname{mex}$ 函数实践：[想了解的点这里](https://blog.csdn.net/qq_74405082/article/details/138728368?ops_request_misc=%257B%2522request%255Fid%2522%253A%252279D38FBD-E1BC-409C-AB3D-F3564067C024%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=79D38FBD-E1BC-409C-AB3D-F3564067C024&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-2-138728368-null-null.142^v100^pc_search_result_base3&utm_term=SG%E5%87%BD%E6%95%B0&spm=1018.2226.3001.4187)
3. 对此题有什么影响：既然是取集合外的最小非负整数，那么就会变成单纯的统计 A 和 B 的数量了（所谓的语法题）。
## 思路
我们只需判断到底是 B 多还是 A 多即可。但是，由于 Alice 为先手，那么 A 大于等于 B，Alice 都会赢。

所以我们可以轻易的得出以下判断：
- 如果 A 的数量大于等于 B，输出 Alice 并换行。
- 反之，输出 Bob 并换行。
## 代码

```cpp
#include<bits/stdc++.h> //代码就如思路一般简单 
#define int long long
using namespace std;
int n,Alice,Bob;
string game;
signed main(){
	scanf("%lld",&n);
	cin >> game;
	for(int i=0;i<=n;i++){
		if(game[i] == 'A') Alice++;
		else if(game[i] == 'B') Bob++;
		if(i == 0) continue;
		if(Alice >= Bob) printf("Alice\n");
		else printf("Bob\n");
	}
	return 0;
}
```

---

## 作者：naoliaok_lovely (赞：1)

# 题目大意
有一个字符串 $s$，两个人 Alice 和 Bob 正进行着一个游戏。设游戏共 $t$ 轮，由 Alice 先手交替进行 $t$ 次操作，单次操作如下：

- 在集合 $X$ 内加入一个非负整数。

最后，令 $ans = \operatorname{mex}\{X\}$，若 $s_{ans}$ 为 `A`，Alice 获胜，$s_{ans}$ 为 `B`，Bob 获胜。在双方都使用最优策略的情况下，求获胜者。

# 解题思路
看到 $\operatorname{mex}$，显然不能直接求，再结合这道题本身是博弈论，于是自然想到 SG 函数——但是想了一会儿发现并非如此。

尝试换一个角度出发：每一个在集合 $X$ 内的数，都不会作为最后的 $ans$。对于 Alice 而言，在上面的启发下，就有了这样的贪心策略：每次操作，选择一个未选择过的 `B`，将它的下标加入集合。并且由于是 $\operatorname{mex}$，应该从前到后选。Bob 同理。容易发现，这样的贪心策略一定是正确的。

在编码时，显然不可能去模拟。稍加思考可以发现，我们只需要比较 `AB` 的数量即可。

# Code
```
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, a, b;
char c[N];

int main()
{
	scanf("%d%s", &n, c);
	c[0] == 'A' ? a++ : b++; 
	for(int i = 1; i <= n; i++)
	{
		c[i] == 'A' ? a++ : b++;
		if(a >= b) puts("Alice");
		else puts("Bob"); 
	}
	return 0;
}
```

---

## 作者：hyl_____ (赞：0)

## 前言 
这道题翻译没有给出 $\mathrm{mex}$ 函数的定义，那么我在此解释一下
>对于由非负整数构成的有限集合 $X$，将满足 $x \notin X$ 的最小非负整数 $x$ 定义为 $\mathrm{mex}(X)$。
## 思路
因为 $\mathrm{mex}(X)$ 的定义是一个不在 $X$ 集合里的一个最小非负整数，所以每回合插入的这个数 $a$ 一定不会是 $\mathrm{mex}(X)$，那么这回合的最终得到的字母 $s_x$ 一定不会是 $s_a$，所以对于两人而言，每一次插入没出现过的第一个对方名字的下标是最优操作。

例如 `Alice` 会插入没出现过的第一个 `B` 的下标，`Bob` 会插入没出现过的第一个 `A` 的下标，

这会让对方的胜利次数变小。而对于每回合来说，两人都会插入对方名字的下标，所以我们要比较次数，即 $s$ 数组中 `A` 和 `B` 出现的次数，若 $sum_a \ge sum_b$，输出 `Alice`，否则输出 `Bob` 即可解出这道题。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	int suma=0,sumb=0;
	for(int i=0;i<=n;++i)
	{
		if(s[i]=='A') suma++;
		else sumb++;
		if(i==0) continue;
//一定要continue，不然会死得很惨，还好题解区有大佬和我一样是从0开始的，不然我还要调几小时
		if(suma>=sumb)cout<<"Alice"<<endl;
		else cout<<"Bob"<<endl;
	}
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

# 思路
题目描述很简单，易懂。很容易发现，$\text{mex(x)}\le i$，所以最优方案是 Alice 取编号最小的 `B`，Bob 取编号最小的 `A`，那么，从后往前选。那么，本题就成为了比较 `AB` 数量了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;int T,cnt1,cnt2;
int main(){
    cin>>T>>s;
    if(s[0]=='A') cnt1++;
    if(s[0]=='B') cnt2++;
    for(int i=1;i<=T;i++){
        if(s[i]=='A') cnt1++;
        if(s[i]=='B') cnt2++;
        if(cnt1>=cnt2) puts("Alice");
        else puts("Bob");
    }
    return 0;
}
```

---

## 作者：fede (赞：0)

# 正文

## 分析

首先理解下翻译中没有的 $\mathrm{mex}()$：[原文链接](https://blog.csdn.net/tanjunming2020/article/details/127267349)
> $\mathrm{mex}(X)$ 指在集合 $X$ 中没有出现过的最小的非负整数，
> 如 $\mathrm{mex}({3,5})=0$，$\mathrm{mex}({0,1,2,3})=4$。

所以题意就是 ~~Alice 和 Bob 又在玩游戏~~：
> 给定一个仅由 `AB` 两种字符组成的长度为 $(n+1)$ 的字符串 $s$。有 $n$ 轮游戏，第 $i$ 轮操作 $i$ 次，每轮由 Alice 先手，后与 Bob 交替进行操作，每次操作加入一个整数 $x$ 到集合 $X$ 中。   
> 当每轮操作游戏结束后，设 $i$ 为集合 $X$ 中没有出现过的最小的非负整数，如果 $s_i$ 为 `A`，则 Alice 获胜，否则 Bob 获胜。   
> **两者都采用最佳策略。**

集合 $X$ 存储的等同于是字符串 $s$ 的下标，由于我们最后要取“集合 $X$ 中没有出现过的”，出现过的也就意味着被删掉了。   
这意味着每一次操作相当于从字符串 $s$ 中删掉一个字符，或者不删（等同于将一个无穷大的数放进集合 $X$），问题也就转变成：
> 一个仅由 `AB` 两种字符组成的长度为 $(n+1)$ 的字符串 $s$。有 $n$ 轮游戏，第 $i$ 轮操作 $i$ 次，每轮由 Alice 先手，后与 Bob 交替进行操作，每次从字符串 $s$ 中删掉一个字符或不做任何操作，剩下字符串的第一个字符如果为 `A`，则 Alice 获胜，否则 Bob 获胜。   
> **两者都采用最佳策略。**

什么叫**两者都采用最佳策略**呢？   
为了获胜，Alice 一定会将离第一个位置最近的 `B` 删掉，Bob 也一定会将离第一个位置最近的 `A` 删掉，只有这样才能让可以使自己获胜的字符往前排。

## 思路

我们需要知道每一轮的赢家是谁。

### 方法一

在第 $i$ 轮中，因为最多会删 $i$ 个字符，所以 Alice 需要删掉前 $i+1$ 个所有为 `B` 的字符，而她一共可以操作 $\lceil\frac{i}{2}\rceil$ 次（向上取整的原因是 Alice 先手）。   
如果可以全部删掉，那么 Alice 获胜，否则 Bob 获胜。

### 方法二

在第 $i$ 轮中，最多会删 $i$ 个字符。   
因为仅有字符串 $s$ 的前 $i+1$ 位起到作用，设 $cnta$ 表示前 $i+1$ 位 `A` 的个数，设 $cntb$ 表示前 $i+1$ 位 `B` 的个数。

如果 $cnta>cntb$，也就是 Bob 要删 `A` 的次数大于 Alice 要删 `B` 的次数，此时 Alice 一定赢。

考虑特殊情况，如果 $cnta=cntb$，也就是 Bob 要删 `A` 的次数等于 Alice 要删 `B` 的次数，~~但是男生要让女生，所以 Alice 赢~~。

但是由于 $cnta+cntb=i+1$，$i+1$ 也就是偶数，而最多会删 $i$ 个字符，也就是奇数个字符，Alice 先手就代表着她能够删的字符更多，此时 Alice 一定赢。   

当然，如果 Alice 不赢，那么就是 Bob 赢。

## 代码

两种时间复杂度都为 $O(n)$，完美通过此题。

### 方法一

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+10;
int n,a,b;
string s;
void get(int x){
	if(s[x]=='B'){
		b++;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	cin>>s;
	get(0);
	for(int i=1;i<=n;i++){
		get(i);
		if(i/2+(i%2!=0)>=b){
			cout<<"Alice"<<endl;
		}else{
			cout<<"Bob"<<endl;
		}
	}
	return 0;
}
```

### 方法二

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+10;
int n,a,b;
string s;
void get(int x){
	if(s[x]=='A'){
		a++;
	}else{
		b++;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	cin>>s;
	get(0);
	for(int i=1;i<=n;i++){
		get(i);
		if(a>=b){
			cout<<"Alice"<<endl;
		}else{
			cout<<"Bob"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：hjqhs (赞：0)

AGC 的题是世界上最有趣的题，某位 Cu 大佬这样说。  
一个集合里的 $\text{mex}$ 绝不会是这个集合里的数。所以对于 Alice，每次选择第一个未出现的 $B$ 的下标加入集合。而 Bob 则是选择第一个未出现的 $A$ 的下标加入集合。简单转换后就变成了比较 $AB$ 的数量。
```cpp
void solve(){
  cin>>n>>s;
  if(s[0]=='A')++cnta;
  if(s[0]=='B')++cntb;
  rep(i,1,n){
    if(s[i]=='A')++cnta;
    if(s[i]=='B')++cntb;
    if(cnta>=cntb)cout<<"Alice"<<'\n';
    else cout<<"Bob"<<'\n';
  }
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_agc063_a)

这题不难。先说一下两个人的博弈策略。

这题 Alice 选的下标所对应的字符一定为 B，Bob 的一定为 A，且两人一定首选小的下标。

因为两人都不能选与自己对应的字符，如果这样只会让自己赢的机会变少，绝对不是最优策略。又因为赢的条件是 $\text{mex}$，所以要把对方对应的字符中最小的下标选择掉。

这一题我有一个与题解区不太一样的做法。

我们可以用两个队列 $a$ 和 $b$ 分别从小到大存储字符串中字符 `A` 和字符 `B` 的下标。接下来循环 $1$ 到 $n$，分别代表第 $k$ 轮。接下来就可以模拟了。如果这个 $k$ 是奇数，说明到 Alice 选择了，就要把选择的字符 `B` 对应的队列 $b$ 的队首出队，因为队首已经被选择了。如果 $k$ 是偶数，那么就要队列 $a$ 的队首出队，跟上一个一样，只是照猫画虎，我就不多说了。

如果我们要判断是谁赢了，那么只要判断两个队列队首的大小就可以了。因为要的是 $\text{mex}$，所以要看现在是哪个留存下来的字符的下标更少。如果是 `A` 就输出 `Alice`，否则输出 `Bob`。

但如果你就这样写你会过不了样例。容易发现，这是因为你的队列已经为空了，但还是要继续判断是谁赢。又容易发现，只要一方的队列为空，那么那一方就一定输。那么我们就可以在循环之前在两个队列的队尾放入一个很大的数，以此在有一方队列为空时，可以直接用这个很大的数与另一方判断，就可以判定为另一方赢。但这个很大的数千万不能出队。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
queue<int> a;
queue<int> b;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n+1;i++)
	{
		char ch;
		cin>>ch;
		if(ch=='A') a.push(i);
		else b.push(i);
	}
	a.push(999999999),b.push(999999999);
	for(register int i=1;i<=n;i++)
	{
		if((i&1)&&b.front()!=999999999) b.pop();
		if(!(i&1)&&a.front()!=999999999) a.pop();
		if(a.front()<b.front()) puts("Alice");
		else puts("Bob");
	}
	return 0;
}
```

---

## 作者：MOwansui (赞：0)

其实可以简化题意，相当于每人每次从队列里去除一个字母，剩下的中下标最小的为    $A$，则 Alice 胜，反之则 Bob 胜，基于贪心，Alice 每次取第一个 $B$，Bob 每次取第一个 $A$，模拟即可

代码
```c++
#include<bits/stdc++.h>
#define fo(xxx) for(int i=1;i<=xxx;++i)
#define int long long
#define N 300005
using namespace std;
int n;
char S[N];
int a[N],idxa;
int b[N],idxb;
signed main()
{
	memset(a,0x3f,sizeof(a));
	memset(b,0x3f,sizeof(b));
	cin>>n;
	cin>>S;
	for(int i=0;i<=n;++i)
	{
		if(S[i]=='A')
		{
			a[++idxa]=i;
		}
		else
		{
			b[++idxb]=i;
		}
	}
	int ta=1,tb=1;
	fo(n)
	{
		if((i&1&&ta<=idxa)||tb>idxb)
		{
			tb++;
		}
		else
		{
			ta++;
		}
		if(a[ta]<b[tb])
		{
			cout<<"Alice\n";
		}
		else
		{
			cout<<"Bob\n";
		}
	}
	return 0;
}
```

---

