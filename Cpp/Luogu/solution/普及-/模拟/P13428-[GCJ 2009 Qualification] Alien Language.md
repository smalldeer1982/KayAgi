# [GCJ 2009 Qualification] Alien Language

## 题目描述

经过多年的研究，Google Labs 的科学家们发现了一种来自遥远星球的外星语言。这种外星语言非常独特，每个单词恰好由 $L$ 个小写字母组成。此外，这种语言中恰好有 $D$ 个单词。

在建立了该外星语言所有单词的字典后，科学家们的下一个重大突破是发现，外星人在过去十年间一直在向地球发送信息。不幸的是，由于两颗星球之间的距离遥远，这些信号在传输过程中被削弱，导致部分单词可能被误解。为了帮助科学家们解读这些信息，他们请你设计一个算法，能够判断给定模式下可能的解释数量。

一个模式恰好由 $L$ 个**符号**组成。每个符号要么是一个小写字母（科学家们非常确定这就是那个字母），要么是由圆括号括起来的一组互不相同的小写字母。例如：(ab)d(dc) 表示第一个字母可以是 a 或 b，第二个字母一定是 d，第三个字母可以是 d 或 c。因此，模式 (ab)d(dc) 可能代表以下 4 种情况之一：add、adc、bdd、bdc。


## 说明/提示

**限制条件**

**小数据集（10 分）**

- $1 \leq L \leq 10$
- $1 \leq D \leq 25$
- $1 \leq N \leq 10$

**大数据集（23 分）**

- $1 \leq L \leq 15$
- $1 \leq D \leq 5000$
- $1 \leq N \leq 500$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3 5 4
abc
bca
dac
dbc
cba
(ab)(bc)(ca)
abc
(abc)(abc)(abc)
(zyx)bc```

### 输出

```
Case #1: 2
Case #2: 1
Case #3: 3
Case #4: 0```

# 题解

## 作者：b__b (赞：3)

~~省流：把思维逆转过来！~~

一种朴素的暴力方法就是生成每一个可能的字符串之后判断：
```cpp
#include <iostream>
#include <set>
std::set<std::string> s;
std::string pd;
int dfs(int ind, std::string tmp) {
    if (ind >= pd.size()) return s.count(tmp);
    if (pd[ind] != '(') return dfs(ind + 1, tmp += pd[ind]);
    int ret = 0, youkuo = ind;
    while (pd[++youkuo] != ')');
    while (++ind < youkuo) ret += dfs(youkuo + 1, tmp + pd[ind]);
    return ret;
}
int main() {
    std::ios::sync_with_stdio(0);
    int l, d, n;
    for (std::cin >> l >> d >> n; d--;) {
        std::string s1;
        std::cin >> s1, s.insert(s1);
    }
    for (int i = 1; i <= n; ++i) std::cin >> pd, std::cout << "Case #" << i << ": " << dfs(0, "") << '\n';
}
```
[于是很成功的 TLE 了。](https://www.luogu.com.cn/record/226865098)

原因是如果每一个符号都有 $26$ 种可能的话，那么最多可以生成 $26^{15}=1677259342285725925376 \approx 1.677 \times 10^{22}$ 个字符串。如果每一个都判断一次绝对会 TLE。

我们发现字典里面最多只会有 $5000$ 个单词，也就是说答案最大只会是 $5000$。于是，让我们把思维逆转过来！我们用字典里面的词语去尝试匹配输入的字符串，最后输出成功匹配的字符串数量：
```cpp
#include <iostream>
std::string pd, dict[5005]; //pd表示当前输入的字符串
//ind表示已经枚举了几个符号，checkind表示检查了几个字符，check表示需要匹配的字符串
bool dfs(int ind, int checkind, const std::string &check) {
    if (ind >= pd.size()) return 1;
    if (pd[ind] != '(') return pd[ind] == check[checkind] ? dfs(ind + 1, checkind + 1, check) : 0;
    int youkuo = ind;
    while (pd[++youkuo] != ')');
    while (++ind < youkuo) if (pd[ind] == check[checkind] && dfs(youkuo + 1, checkind + 1, check)) return 1;
    return 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    int l, d, n;
    std::cin >> l >> d >> n;
    for (int i = 0; i < d; ++i) std::cin >> dict[i];
    for (int i = 1; i <= n; ++i) {
        std::cin >> pd;
        int ans = 0;
        for (int i = 0; i < d; ++i) if (dfs(0, 0, dict[i])) ++ans;
        std::cout << "Case #" << i << ": " << ans << '\n';
    }
}
```
时间复杂度分析：匹配时最多枚举 $L \times W$（$W$ 为字符集大小，本题中只有小写字母，因此 $W=26$）个字符，对于每一个输入的字符串需要拿字典里面的 $D$ 个字符串去匹配，$N$ 个输入，时间复杂度为 $O(N \times D \times L \times W)$，可以通过本题。

---

## 作者：DreamInk (赞：3)

# 思路
首先要如何知道一个模式串能组成那些单词？知道的话，只要一个个对比外星语言已知的单词就能很快解决问题。

### Part.1
我们可以把每个模式串 $s$ 给“解密”。创建一个桶数组 $t$，将每一位能用那些字母给存下来。**注意：由于有多个模式串，所以要记得每次清空 $t$ 数组。**

例如模式串 $(ab)b(bc)$ 对应存储的桶数组应如下。
```
t[1][1]=1;//第一位能用 a，存储时将 a 换成对应的数字。如 a对应1，b对应2，c对应3，d对应4 
t[1][2]=1;//第一位能用 b，存储时b对应2 
t[2][2]=1;//第二位能用 b 
t[3][2]=1;//第三位能用 b
t[3][3]=1;//第三位能用 c，存储时c对应3 
```

```cpp
string a;
cin>>a;
int id=0;//记录这是单词的第几位 
memset(t,0,sizeof t);//每次清空！！！ 
for(int i=0;i<a.size();i++){//开始“解密 ” 
    if(a[i]=='('){//这一位可以用多个字母的情况 
      id++;
      while(a[++i]!=')')  t[id][int(a[i]-'a')+1]=1;//表示第id位，可以用a[i]这个字母，t数组对应的位置要标1（就代表可以用） 
    }
    else t[++id][int(a[i]-'a')+1]=1;//第id位只能用这一个字母a[i] 
}
```
### Part.2
接下来，我们枚举外星语言已知的单词，用 $f$ 来表示能不能匹配。如果这个单词每一位字母 $s_i$，模式串相对应的那一位 $t_i$ 能用 $s_i$ 这个字母的话，代表这一位就匹配成功，当然每一位都要匹配成功才算匹配这个单词。

```cpp
int ans=0;//统计能匹配成功的单词 
for(int i=1;i<=d;i++){
   bool f=0;
   for(int j=0;j<s[i].size();j++){
       int q=int(s[i][j]-'a')+1;
       if(t[j+1][q]==0){//这一位不能用这个字母，这个单词不能匹配 
          f=1;//标记 
          break;//直接退出，没必要继续匹配下去 
       }
   }
   if(f==0)ans++;//累加匹配成功的单词
}
```
核心代码都给你们了，主程序对于你们应该小菜一碟了。
# 完结散花
如果对你有用的话，就点个赞吧！

---

## 作者：Il1_1_3 (赞：3)

# P13428 题解

~~蒻蒻地说一句我好像是这道题首 A。~~

## 题意

如题，先读入字典里已知的单词，再读入 $N$ 个模式串，其中模式串中括号内的部分代表不确定的字符，问每个模式串可能匹配多少个字典里的单词。

## 思路
先建一个字符串数组存储字典。

对于每个模式串，循环遍历字典中的单词，如果能匹配就将答案 $+1$。

对于模式串，如果遇到左括号（即 `(`），在遇到右括号之前，分析每个括号里的字符，如果它和当前字典里的单词的对应位置相同，那么就将当前的标志变量（代码中变量名为 $bit$）设为真。如果括号里的都不匹配，就直接跳转到下一个**单词**。

对于没有括号的字符，直接判断即可。

**注意输出冒号和数之间有一个空格！**

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() 
{
    int l,d,n;string s[5003];
    cin >> l >> d >> n;
    for(int i=0;i<d;i++)
        cin >> s[i];
    for(int k=1;k<=n;k++)
	{
        string str;
        cin >> str;
        int cnt=0;
        for(int i=0;i<d;i++)
		{
            bool flg=1;int pos=0;
            for (int j=0;j<l;j++)
			{
                if(str[pos]=='(') 
				{
                    bool bit=0;
                    pos++;
                    while(str[pos]!=')')
                    {
                    	if(str[pos]==s[i][j])
							bit=1;
						pos++;
					}   
					pos++;
                    if(!bit){flg=0;break;}
                }
				else if(str[pos++]!=s[i][j]){flg=0;break;}
            }
            if(flg) cnt++;
        }
        cout << "Case #" << k << ": " << cnt << '\n';
    }
    return 0;
}
```

---

## 作者：HP_Serenity (赞：2)

将输入的模式字符串解析成 $L$ 个位置的可选字符集合。那么对于字典中的每个单词，检查其每个字符是否在对应位置的可选集合中。如果所有字符都匹配，则该单词有效。对每个模式，统计字典中匹配的单词数量。我们再用上集合，让查找效率变成 $O(1)$。
```c++
#include <bits/stdc++.h>
using namespace std;
int l, d, n;
char w[5005][20], pa[5005];
bool v[26];
int main() {
    scanf("%d%d%d", &l, &d, &n);
    for(int i=0; i<d; i++) scanf("%s", w[i]);
    for(int c=1; c<=n; c++) {
        scanf("%s", pa);
        vector<set<char>> op(l);
        int pos = 0, cnt = 0;
        for(int i=0; pa[i]&&pos<l; ) {
            if(pa[i]=='(') {
                i++;
                while(pa[i]!=')') {
                    op[pos].insert(pa[i]);
                    i++;
                }
                i++;
            } else {
                op[pos].insert(pa[i]);
                i++;
            }
            pos++;
        }
        for(int i=0; i<d; i++) {
            bool mt = 1;
            for(int j=0; j<l; j++) {
                if(op[j].find(w[i][j])==op[j].end()) {
                    mt = 0;
                    break;
                }
            }
            if(mt) cnt++;
        }
        printf("Case #%d: %d\n", c, cnt);
    }
    return 0;
}
```

---

## 作者：bayiran (赞：1)

## 解题思路
1. ‌分解：将每个测试用例的字符串分解为 $L$ 个字符集合，每个集合表示该位置可能的字母，这个集合可能有很多个字符，也可能只有一个。
2. 检查‌：对于每个合法字符串，检查其每个位置的字符是否在上一步的对应位置的字符集合中。
3. 统计‌：统计所有匹配的单词数量。


### 优化
- 在检查单词匹配时，一旦发现某个位置的字母不在模式对应集合中，即可终止当前单词的检查，减少时间浪费。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string> dic;

//对应上面的第2步
bool pd(string w,vector<string> p){
    for(int i=0;i<w.size();i++){
        if(p[i].find(w[i]) == string::npos){
            return 0;
        }
    }
    return 1;
}

//对应上面的第1步
vector<string> pp(string &s){
    vector<string> pa;
    int i = 0;
    while(i < s.size()){
        if(s[i] == '('){
            string op;
            i++;
            while(s[i] != ')'){
                op += s[i];
                i++;
            }
            i++;
            pa.push_back(op);
        }
        else{
            pa.push_back(string(1,s[i]));
            i++;
        }
    }
    return pa;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int L,D,N;
    cin>>L>>D>>N;
    dic.resize(D);
    for(int i=0;i<D;i++){
        cin>>dic[i];
    }
    for(int i=1;i<=N;i++){
        string p;
        cin>>p;
        vector<string> ppp = pp(p);
        int cnt = 0;
        for(string ww : dic){
            if(pd(ww,ppp)){
                cnt++;
            }
        }
        cout<<"Case #"<<i<<": "<<cnt<<endl;
    }
    return 0;
}

```

时间复杂度 $O(DL+NL)$，用时大约 $60$ ms，交题解时最优解排第二，距离榜一 $33$ ms 有点远，膜拜 
DreamInk!

---

## 作者：Shadow_T (赞：1)

## 题目分析

来复健题解了。

注意到：

- $1 \leq L \leq 15$。

- $1 \leq D \leq 5000$。

- $1 \leq N \leq 500$。

我们考虑怎么去打这个暴力。

如果我们把询问字符串的所有情况拆出来去判断，复杂度最坏达到了 $O(N\times 26^L)$，是无法通过的。

我们发现在这 $26^L$ 的情况数中，只有最多 $D$ 个单词才是有效的。$D$ 比较小，我们直接对于每一个询问枚举单词库中的单词，判断是否满足询问串的要求。

这是很好做的，我们遇到左括号的时候就一直往后走直到右括号，把这个位置所有可以的字符种类的统计出来。如果没有括号，就直接取这一位的字符。然后判断当前这个单词库的单词的这一位是否在这一位字符的情况中被包含。

很明显复杂度 $O(N\times D \times L)$ 的代码最多只会跑 $3.75 \times 10^7$，是可以在两秒内轻松通过的。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
vector<string> mp;
bool vis[27];
int main()
{
    int l,d,n;
    cin>>l>>d>>n;
    while(d--)
    {
        string s;
        cin>>s;
        mp.push_back(s);
    }
    for(int Case=1;Case<=n;Case++)
    {
        string s;
        cin>>s;
        int ans=0;
        for(int i=0;i<mp.size();i++)
        {
            string it=mp[i];
            int tot=0;
            bool p=1;
            for(int i=0;s[i];i++)
            {
                memset(vis,0,sizeof vis);
                if(s[i]=='(')
                {
                    i++;
                    while(s[i]!=')') vis[s[i]-'a']=1,i++;
                }
                else vis[s[i]-'a']=1;
                if(!vis[it[tot]-'a'])
                {
                    p=0;
                    break;
                }
                tot++;
            }
            if(p) ans++;
        }
        cout<<"Case #"<<Case<<": "<<ans<<"\n";
    }
}
```

[R226643343](https://www.luogu.com.cn/record/226643343)

---

