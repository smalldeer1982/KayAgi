# [USACO23OPEN] Moo Language B

## 题目描述

### 题目背景

FJ 对与奶牛更好地互动感兴趣，所以他决定学习 moo 语言！


moo 语言与英语相似，但更为简单。单词只有四种类型：名词、及物动词、不及物动词和连词，每两个单词之间必须用空格隔开。标点符号仅包含逗号和句号，它会跟在单词后面，若该标点符号后面存在单词，则需要隔一个空格再放单词。

对于每个句子，都需要遵循以下格式中的一条：

1. 名词+不及物动词。
2. 名词+及物动词+名词（可以有多个）。及物动词后面必须有至少一个名词。除及物动词后面的第一个名词外，后面的每个名词前面都必须加一个逗号。

也可以在两个句子之间加一个连词，形成复合句，复合句不能与其他句子用连词连接。每一个句子（包括复合句）都必须以句号结尾。

FJ 的词库中有 $N$ 个单词、$C$ 个逗号和 $P$ 个句号。每个单词的使用次数不能超过这个单词在词库中出现的次数。现在，你要帮他输出几个符合以上要求的句子，使总单词数尽量多。

每个输入文件中共包含 $T$ 组样例。

## 说明/提示

$1 \leq T \leq 100$，$1 \leq P, C \leq N \leq 10^3$。

- 输入 2-6：$N \leq 10$。
- 输入 7-11：$N \leq 100$。
- 输入 12-16：$N \leq 1000$。
- 输入编号除以 5 余 2 的测试点：没有及物动词。
- 输入编号除以 5 余 3 的测试点：没有不及物动词。
- 输入编号除以 5 余 4 的测试点：没有连词。

translated by [liyuanchen2021](https://www.luogu.com.cn/user/557680)

## 样例 #1

### 输入

```
3
1 1 1
bessie noun
10 5 4
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
24 5 4
but conjunction
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
bob noun
impressed transitive-verb
cow noun
impressed transitive-verb
leaped intransitive-verb
elsie noun
bella noun
buttercup noun
pushed transitive-verb
mooed intransitive-verb
envy noun
john noun
nhoj noun
```

### 输出

```
0

9
nhoj mooed. farmer taught elsie, bessie and john flew.
23
nhoj mooed. nhoj impressed john, farmer, elsie, bessie and cow impressed bob. bella pushed elsie and buttercup flew. envy mooed but john leaped.```

# 题解

## 作者：_LRH_ (赞：5)

# USACO 的模拟

## 题面

[题目传送门](https://www.luogu.com.cn/problem/P9184)

## 题目思路

* 逗号必定和名词放一起

* 连词要尽量多使用

* 先计算语句的总数（尽量多)，设 s 为句子的总数量， o 为连词数。 $s = p + \min(p, o)$

* 先尽量多的用不及物动词

* 在尽量多的用及物动词

* 由于使用及物动词可以多消耗名词，所以尽量将不及物动词语句替换成及物动词的句子

* 由于逗号可以和名词一一搭配，所以把他们加入一个及物动词语句内。

* 统计词数，输出所有语句（记得加上连词）

## 题目代码

```cpp

#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

int t, n, c, p, sum, h, l;

vector<string> a[5], ans[N];  // 0 名词，1 连词，2 及物动词， 3 不及物动词  语句

int main() {
  for (cin >> t; t; t--, sum = h = l = 0) {
    cin >> n >> c >> p;
    for (int i = 0; i < 4; i++) {
      a[i].clear();
    }
    for (int i = 1, o; i <= n; i++) {
      string s, t;
      cin >> s >> t;
      if (t[0] == 'n') {
        o = 0;
      } else if (t[0] == 'c') {
        o = 1;
      } else if (t[0] == 't') {
        o = 2;
      } else {
        o = 3;
      }
      a[o].push_back(s);
    }
    p = p + min(p, (int)a[1].size()); // 句子数
    for (; a[0].size() && a[3].size() && h < p; sum += 2) {  
      ans[++h] = a[4];
      ans[h].push_back(a[0].back()), ans[h].push_back(a[3].back());
      a[3].pop_back(), a[0].pop_back();
    } // 尽量多的不及物语句
    for (l = h; a[0].size() >= 2 && a[2].size() && h < p; sum += 3) { 
      ans[++h] = a[4];
      ans[h].push_back(a[0].back()), ans[h].push_back(a[2].back());
      a[2].pop_back(), a[0].pop_back();
      ans[h].push_back(a[0].back()), a[0].pop_back();
    } // 尽量多的及物语句
    for (; l && a[0].size() && a[2].size(); l--, sum++) {
      ans[l].pop_back();
      ans[l].push_back(a[2].back()), ans[l].push_back(a[0].back());
      a[0].pop_back(), a[2].pop_back();
    } // 尽量将不及物语句替换成及物语句
    for (; l != h && a[0].size() && c; c--, sum++) {
      ans[h].push_back(a[0].back()), a[0].pop_back();
    } // 在及物语句乃加入尽可能多的名词及逗号
    cout << sum + min(h / 2, (int)a[1].size()) << '\n'; // 单词数
    for (int i = 1; i <= h; i++) {
      for (int j = 0; j < ans[i].size(); j++) {
        if (j > 2) {
          cout << ",";
        }  
        if (j) {
          cout << " ";
        }
        cout << ans[i][j];
      }
      if (i < h) { // 如果还有句子
        if (i % 2 && a[1].size()) { // 还可以使用连词
          cout << ' ' << a[1].back() << ' ';
          a[1].pop_back();
        } else {
          cout << ". "; // 不然输出句号
        }
      }
    }
    if (sum) {
      cout << "." << "\n"; // 最后的要输出句号， 如果没有句子就什么也不输出
    }
  }
  return 0;
}

---

## 作者：Error_Eric (赞：3)

### 题意

[Link](https://www.luogu.com.cn/problem/P9184)

（看来大家都不想写模拟题的题解，那我稍微提供一下我的思路，时间复杂度和思路都不一定是最优的，如果有更好的方法欢迎提出。）

### Sol

本题的最大难点个人认为是名词不容易判断分配到那种句型更优。但是不难发现的是，如果我们已经确定了 ``intransitive-verb`` 句型（句型 1 ）和 ``transitive-verb`` 句型（句型 2 ）的个数，那么就比较好判断是否存在合法方案了。同时在这种情况下也比较容易构造单词数最多的解。

这种先猜答案后验证的过程很像二分，不过不难发现这题并不好二分。但是由于 $N$ 比较小完全可以用枚举答案的方式解决。

因此本题的算法为：

1. 枚举句型 1 的个数 $x$ 和句型 2 的个数 $y$。

2. 确保 ``.`` 和连词个数足够

3. 分配主语和宾语，确定名词个数足够。

4. 计算宾语并列最多次数，并算出当前条件下最多的单词数。

5. 迭代答案。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<numeric>
#include<vector>
#include<functional>
using namespace std;
vector<string> nn,tv,iv,cj;
string word,pos;
int t,n,c,p,ans,ax,ay;
const int inf=1e9;
void add(char ch,string ele){ // 将单词分类加入词典
    switch(ch){
    case 'n':nn.push_back(ele);break;
    case 't':tv.push_back(ele);break;
    case 'i':iv.push_back(ele);break;
    case 'c':cj.push_back(ele);break;
    default: cout<<"noo"<<endl;break;
    }
}
void test(int s1,int s2){
    if(p*2<s1+s2||p+cj.size()<s1+s2) return; // 确保句号+连词够用，注意句号至少要占一半。
    int rn= nn.size()-s1-s2-s2, // 剩余的名词个数，<0表示当前尝试非法。
    uc= min((int)cj.size(),(s1+s2)/2), // 最多可以使用多少个连词
    nc= min({c,rn,(s2>0?inf:0)}), // n.s after comma
    res=s1*2+s2*3+nc+uc;
    if(/*rn>=0 && */nc>=0 && res > ans) 
        ans=res,ax=s1,ay=s2;
    return;
}
vector<string> ansr;
void out(){
    if(ans<0) {cout<<0<<endl; return;}
    cout<<ans<<endl,ansr.clear();
    auto tpop=[&](vector<string>&vv){
        auto resr=vv.back(); vv.pop_back();
        return resr;
    };
    for(int i=1;i<=ax;i++)
        ansr.push_back(tpop(nn)),ansr.push_back(tpop(iv)),ansr.push_back("#");
    for(int i=1;i<=ay;i++){
        ansr.push_back(tpop(nn)),ansr.push_back(tpop(tv)),ansr.push_back(tpop(nn));
        if(i==ay){
            while ((c--)&&nn.size()){
                ansr.push_back(","),ansr.push_back(tpop(nn));
            }
        }
        ansr.push_back("#");
    }
    bool lastisconj=0;//句号+连词 单独处理
    for(int i=0;i<ansr.size();i++){
        if(ansr[i][0]=='#'){
            if(i<ansr.size()-1&&cj.size()&&(lastisconj^=1))
                ansr[i]=tpop(cj);
            else 
                ansr[i]=".";
        }
    }
    for(int i=0;i<ansr.size();i++){
        cout<<ansr[i];
        if(i<ansr.size()-1&&ansr[i+1][0]!=','&&ansr[i+1][0]!='.')
            cout<<' ';
    }
    cout<<endl;
}
void mian(){
    cin>>n>>c>>p,ans=-1,ax=0,ay=0,
    nn.clear(),tv.clear(),iv.clear(),cj.clear();
    for(int i=1;i<=n;i++)
        cin>>word>>pos,add(pos[0],word);
    for(int x=0;x<=iv.size();x++)//枚举
        for(int y=0;y<=tv.size();y++)
            test(x,y);//验证答案
    out();//输出
}
int main(){
    ios::sync_with_stdio(0),cin>>t;
    while(t--) mian();
}
```

---

## 作者：foryou_ (赞：2)

恶♂趣♂味♂大♂模♂拟♂。

首先是构造语句部分：

- 开始肯定是尽可能地多用上不及物语句和及物语句；

- 接着，因为及物语句的单词数量一定比不及物语句多，所以贪心地尽可能多地将不及物语句改为及物语句；

- 然后，为了增加语句长度，再次贪心地在及物语句中尽可能多地添加名词和逗号即可。

接下来是输出部分：

- 对于一个语句中的单词，若其编号 $\ge 1$，则需要输出空格；若其编号 $\ge 3$，则需要输出逗号；

- 对于不是最后一句的语句，若它还能够与其他语句通过连词相连，则使用一个连词。

代码：

```cpp
void solve(){
	//读入与初始化
	cin>>n>>c>>p,sum=tot=ttot=0;
	for(int i=0;i<4;i++) a[i].clear();
	for(int i=1;i<=n;i++){
		string s,op; cin>>s>>op;
		if(op[0]=='n') a[0].push_back(s);
		else if(op[0]=='t') a[1].push_back(s);
		else if(op[0]=='i') a[2].push_back(s);
		else a[3].push_back(s);
	}
	
	p+=min(p,(int)(a[3].size())); //计算语句总数
	for(;a[0].size()&&a[2].size()&&tot<p;sum+=2){ //使用不及物语句
		ans[++tot]=a[4];
		ans[tot].push_back(a[0].back()),ans[tot].push_back(a[2].back());
		a[0].pop_back(),a[2].pop_back();
	}
	for(ttot=tot;a[0].size()>=2&&a[1].size()&&tot<p;sum+=3){ //使用及物语句
		ans[++tot]=a[4];
		ans[tot].push_back(a[0].back()),ans[tot].push_back(a[1].back());
		a[0].pop_back(),a[1].pop_back();
		ans[tot].push_back(a[0].back());
		a[0].pop_back();
	}
	for(;ttot&&a[0].size()&&a[1].size();ttot--,sum++){  //尽量用及物语句替代不及物语句
		ans[ttot].pop_back();
		ans[ttot].push_back(a[1].back()),ans[ttot].push_back(a[0].back());
		a[0].pop_back(),a[1].pop_back();
	}
	for(;ttot!=tot&&a[0].size()&&c;c--,sum++) //添加名词和逗号
		ans[tot].push_back(a[0].back()),a[0].pop_back();

	cout<<sum+min(tot/2,(int)(a[3].size()))<<'\n'; //输出语句总数
	for(int i=1;i<=tot;i++){
		for(int j=0;j<ans[i].size();j++){
			if(j>2) cout<<',';
			if(j) cout<<' ';
			cout<<ans[i][j];
		}
		if(i<tot){
			if(i%2&&a[3].size()) //若能够使用连词
				cout<<' '<<a[3].back()<<' ',a[3].pop_back();
			else cout<<". ";
		}
	}
	if(sum) cout<<".\n"; //若有答案才输出句号
}
```

---

## 作者：Union_Find (赞：0)

其实这道题细节还挺多的。

首先容易想到的是，不及物动词的优先级高于及物动词，所以可以先放不及物动词，再放及物动词。原因也很简单，都是使用了 $2$ 个名词，不及物动词有 $4$ 个，及物动词只有 $3$ 个。

下一步很重要。如果句号用完了，此时及物动词优先级高于不及物动词，因为一句话，及物动词至少有 $3$ 个单词，而不及物动词只有 $2$ 个。所以我们要用及物动词替换不及物动词。

最后是输出的细节。注意标点前面不要空格，行末不要有空格，但是少输出空行是可以的。

代码补充。使用 vector <int> ans[3005]，其中下标就是第几句话。这里将连词默认成一句话，且连词优先级高于句号，因为多了一个词。注意一句话至多一个连词。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll T, n, c, p, nn, jjn, bn, ln, vis[1005], kkk, mp[1005], sum;
string s[1005], t;
vector <ll> ans[3005]; 
void wt(string s){cout << s;}
void find(ll x){
	for (int i = 1; i <= n; i++) if (mp[i] == x && !vis[i]){
		vis[i] = 1;
		cout << s[i];
		return ;
	}
}
int main(){
	scanf ("%lld", &T);
	while (T--){
		scanf ("%lld %lld %lld", &n, &c, &p);
		nn = jjn = bn = ln = kkk = sum = 0;
		for (int i = 1; i <= n; i++){
			ans[i].clear();
			vis[i] = 0;
			cin >> s[i] >> t;
			if (t[0] == 'n') mp[i] = 1, nn++;
			else if (t[0] == 't') mp[i] = 2, jjn++;
			else if (t[0] == 'i') mp[i] = 3, bn++;
			else mp[i] = 4, ln++;
		}
		p = p + min(p, ln);
		while (nn && bn && kkk < p){
			ans[++kkk].push_back(1);
			ans[kkk].push_back(3);
			nn--, bn--, sum += 2;
		}
		ll kk = kkk;
		while (nn >= 2 && jjn && kkk < p){
			ans[++kkk].push_back(1);
			ans[kkk].push_back(2);
			ans[kkk].push_back(1);
			nn -= 2, jjn--, sum += 3;
		}
		while (kk && nn && jjn){
			ans[kk].pop_back();
			ans[kk].push_back(2);
			ans[kk].push_back(1);
			nn--, jjn--, kk--, sum++;
		}
		while (kk != kkk && nn && c){
			ans[kkk].push_back(1);
			nn--, c--, sum++;
		}
		printf ("%lld\n", sum + min(kkk >> 1, ln));
		for (int i = 1; i <= kkk; i++){
			for (int j = 0; j < ans[i].size(); j++){
				if (j > 2) wt(",");
				if (j) wt(" ");
				find(ans[i][j]);
			}
			if (i < kkk)
				if ((i & 1) && ln && i != kkk) wt(" "), find(4), wt(" "), ln--;
				else wt(". ");
		}
		if (sum)
			puts(".");
	}
	return 0;
}

```

---

## 作者：raozf (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9184)

### 题意

有一套语法规则，给定可以使用的单词以及标点符号的数量，要求构造一个使用了最多单词的语句序列。

### 思路

首先需要对语法规则进行分析，简化问题并找到切入点：
1. 逗号只能用来和名词进行一比一搭配，放到带及物动词的语句后面，所以可以最后再考虑。此时需要至少有一个带及物动词的语句。
2. 使用连词可以增加单词数量，而且还能增加语句数量的上限，应当尽量多使用。但是也可以先构造句子，最后再进行连接。
3. 名词和不及物动词可以一比一搭配，和及物动词可以二比一搭配，最优的搭配方法取决于每种单词的数量。

不难发现，上述第三条是最复杂的，名词多的时候跟及物动词搭配更好，名词少的时候跟不及物动词搭配更好，但是有可能受到语句数量的限制。想要直接计算出每种语句的数量比较困难，采用构造再调整的策略会简单一些。所以我们不妨尝试由简至繁来进行构造：
1. 首先计算语句的总数量，每个连词与一个句号搭配可以让总数加 $1$，所以总增量不能超过句号数量。
2. 先尽量多构造不及物动词语句。
3. 再尽量多构造及物动词语句。
4. 考虑及物动词语句可以在一个语句中消耗更多名词，所以尽量将不及物动词语句替换成及物动词语句。
5. 考虑逗号和多余的名词搭配，放到任意及物动词语句的后面。
6. 计算可以使用连词的数量并累加到答案中，最后输出所有的语句。

### 复杂度

令单词长度为 $O(L)$，本题中 $L=10$。

#### 时间复杂度

构造时每个单词最多操作 $2$ 次，总共 $O(NL)$。

#### 空间复杂度

记录单词 $O(NL)$。

---
# code:

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int kMaxN = 2001;
int t, n, c, p, s, m, l;
vector<string> w[5], a[kMaxN];  // 0 名词，1 连词，2 及物动词， 3 不及物动词
int main() {
  for (cin >> t; t; t--) {
    cin >> n >> c >> p;
    fill(w, w + 4, w[4]), s = m = l = 0;  // 初始化
    for (int i = 1; i <= n; i++) {
      string s1, s2;
      cin >> s1 >> s2;
      w[(s2[0] == 't' || s2[0] == 'i') * 2 + (s2[0] == 'c' || s2[0] == 'i')].push_back(s1);  // 分类存放单词
    }
    p += min(p, (int)w[1].size());                         // 连词增加句子数量
    for (; w[0].size() && w[3].size() && m < p; s += 2) {  // 使用不及物动词构造新句
      a[++m] = w[4];                                       // 创建新句
      a[m].push_back(w[0].back()), w[0].pop_back();        // 加入名词
      a[m].push_back(w[3].back()), w[3].pop_back();        // 加入不及物动词
    }
    for (l = m; w[0].size() >= 2 && w[2].size() && m < p; s += 3) {  // 使用及物动词构造新句
      a[++m] = w[4];                                                 // 创建新句
      a[m].push_back(w[0].back()), w[0].pop_back();                  // 加入名词
      a[m].push_back(w[2].back()), w[2].pop_back();                  // 加入及物动词
      a[m].push_back(w[0].back()), w[0].pop_back();                  // 加入名词
    }
    for (; l && w[0].size() && w[2].size(); l--, s++) {  // 将不及物动词句改造成及物动词句
      a[l].pop_back();                                   // 去掉不及物动词
      a[l].push_back(w[2].back()), w[2].pop_back();      // 加入及物动词
      a[l].push_back(w[0].back()), w[0].pop_back();      // 加入名词
    }
    for (; l != m && w[0].size() && c; c--, s++) {   // 加入多余的名词和逗号
      a[m].push_back(w[0].back()), w[0].pop_back();  // 加入名词
    }
    cout << s + min(m / 2, (int)w[1].size()) << '\n';             // 累加连词数量
    for (int i = 1; i <= m; i++) {                                // 枚举句子
      for (int j = 0; j < a[i].size(); j++) {                     // 枚举单词
        cout << (j > 2 ? "," : "") << (j ? " " : "") << a[i][j];  // 输出单词，判断是否需要输出逗号和空格
      }
      if (i < m) {                   // 之后还有句子
        if (i % 2 && w[1].size()) {  // 可以使用连词
          cout << ' ' << w[1].back() << ' ';
          w[1].pop_back();
        } else {
          cout << ". ";
        }
      }
    }
    cout << (s ? "." : "") << '\n';
  }
  return 0;
}

---

