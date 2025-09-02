# Ugly Pairs

## 题目描述

给定一个只包含小写拉丁字母的字符串。

如果字符串中一对相邻的字母在字母表中也是相邻的，则称这对字母为“丑陋对”。例如，字符串 "abaca" 在位置 $(1, 2)$ — "ab" 和 $(2, 3)$ — "ba" 处包含丑陋对。字母 'a' 和 'z' 不被认为在字母表中相邻。

你能否重新排列给定字符串的字母，使得其中不包含任何丑陋对？你可以任意排列字符串中的字母，但不能添加或删除字母，也可以保持原顺序不变。

如果有多种答案，输出任意一种即可。

你需要回答 $T$ 个独立的询问。

## 说明/提示

在第一个样例中，"bdac" 也是正确答案。

第二个样例说明只有字母表中相邻的字母不能相邻。相同字母可以相邻。

第三个样例有很多合法答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
abcd
gg
codeforces
abaca
```

### 输出

```
cadb
gg
codfoerces
No answer
```

# 题解

## 作者：rui_er (赞：8)

本文是我的 CF 思维题集锦的第三期，[点我返回索引](https://www.luogu.com.cn/blog/ak-ioi/codeforces-0)。

原题链接：[1156B Ugly Pairs](https://codeforces.com/problemset/problem/1156/B) (dfs and similar, greedy, implementation, sortings, strings, \*1800)

**题意简述**

对字符串进行排序，使相邻的两个字母在字母表不相邻。

**解法分析**

考虑当字符的奇偶性相同时一定可以排到一块，因此我们按照 `a` 到当前字符的偏移量的奇偶性将原字符串拆分为两个，并分别进行排序。然后将这两个字符串首尾相接，判断是否符合要求即可。

代码很短也很好写。

**代码**

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 105;

char s[N], a[N], b[N];

int main() {
	mulT0 {
		scanf("%s", s+1);
		int n = strlen(s+1), LA = 0, LB = 0;
		rep(i, 1, n) {
			if((s[i] - 'a') & 1) a[++LA] = s[i];
			else b[++LB] = s[i];
		}
		a[LA+1] = b[LB+1] = '\0';
		sort(a+1, a+1+LA);
		sort(b+1, b+1+LB);
		if(abs(a[LA] - b[1]) != 1) printf("%s%s\n", a+1, b+1);
		else if(abs(b[LB] - a[1]) != 1) printf("%s%s\n", b+1, a+1);
		else puts("No answer");
	}
	return 0;
}
```

---

## 作者：installb (赞：5)

## 前言  
这种多解题  
样例输出仅仅是帮助理解题目意思用的  
不要去参考它  
往往不可能输出与样例输出相同  
## 正文  
给一个字符串排序  
换个思路 就是给你一定数量的a~z字母 把它们组合起来  
由于只要不相邻 相同的字母就全部摆在一起  

然后这题就变成给定一些字母 把它们按一定顺序排序 保证任意两个相邻的字符不是相邻字母  

**本题做法: 构造**  
我们先假设26个字母都有 让我们构造一个序列出来 满足题目意思  
```cpp
acegikmoqsuwybdfhjlnprtvxz
```  
**但是这样还不行**  
比如 假设c~y/e~y/e~b(仅举三个例子)这些字母全部没有  
就会出现相邻的状况  

解决方法: 再构造一个  
把b开始后面一半移动到前面 这样可以保证  
如果有解 不符合第一个的 一定符合下面这个:  
```cpp
bdfhjlnprtvxzacegikmoqsuwy
```  
**上面如果缺少中间一段导致相邻 这个字符串可以保证缺少的是这两相邻字符一直到两端**  
~~太抽象了?举个例子吧~~  
```cpp
ace-----------dfhj-np---xz
-dfhj-np---xzace----------
```  
都不行的话 一定无解  
**只有连续的两个字符或连续的三个字符会造成无解的情况**

统计每个字符数量  
依次判断两种情况  
然后满足则输出答案  

主要在上面讲了 注释就不太详细了
## code:
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

int T;
int cnt[150] = {0}; // 记录字符数量
string s,t,m,n,j1,j2;

char judge(string x){
	int len = x.length();
	for(int i = 1;i < len;i ++){
		if(abs(x[i] - x[i - 1]) == 1) return 0;
	}
	return 1; // 这个是用来判断两种构造是否可行的
}

int main(){
	ios::sync_with_stdio(false);
	m = "acegikmoqsuwybdfhjlnprtvxz";
	n = "bdfhjlnprtvxzacegikmoqsuwy"; // 构造
	cin >> T;
	while(T --){
		memset(cnt,0,sizeof(cnt)); // 多测清空
		cin >> s; j1 = ""; j2 = "";
		int len = s.length();
		for(int i = 0;i < len;i ++) cnt[s[i]] ++; // 记录字母出现次数(也可以用map)
		for(int i = 0;i < 26;i ++){
			for(int j = 1;j <= cnt[m[i]];j ++){
				j1 += m[i]; // 第一次构造 按m的字母顺序一个个加上去
			}
		}
		if(judge(j1)){ // 判断
			cout << j1 << endl; // 第一个可行
			continue;
		}
		for(int i = 0;i < 26;i ++){
			for(int j = 1;j <= cnt[n[i]];j ++){
				j2 += n[i]; // 第二次构造
			}
		}
		if(judge(j2)){
			cout << j2 << endl; // 第二个可行
			continue;
		}
		cout << "No answer" << endl; // 无解
	}
	return 0;
}
```  
**多测清空!**

---

## 作者：世末OIer (赞：2)

对于所有相同的字母，我们都放在一起（这样也不会犯规）

现在只需要搜索出那最多26个字母的顺序即可

```cpp
#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#define ll long long
using namespace std;
int cnt[30]/*统计个数*/,n;
bool ok=0;
string s;
bool use[33];                //当前字母是否用过
int _C;                    //记录字母种类的个数
inline void dfs(int x,int lst){   //x:第x个位置 lst:上一个位置的颜色
	if(x==_C){
		ok=1;
		return;
	}
	for(int i=0;i<26;++i){
		if(abs(i-lst)>1 and !use[i] and cnt[i]){
			use[i]=1;
			v.push_back(i);
			dfs(x+1,i);
			if(ok) return;
			use[i]=0;
			v.pop_back();
		}
	}
}
inline void solve(){
	ok=0;
	_C=0;
	memset(cnt,0,sizeof(cnt));
	memset(use,0,sizeof(use));
	cin>>s;
	v.clear();
	int i,j;
	for(i=0;i<s.size();++i) cnt[s[i]-'a']++;  //统计
	for(i=0;i<26;++i) if(cnt[i]) ++_C;      //统计
	dfs(0,-123);                     //开始搜索
	if(!ok){
		cout<<"No answer\n";
		return;
	}
	for(i=0;i<v.size();++i) for(j=0;j<cnt[v[i]];++j) cout<<(char)('a'+v[i]);
	cout<<endl;
}
int main(){
	int i,j;
	int T;
	cin>>T;
	while(T--) solve();
}
```

---

## 作者：info___tion (赞：1)

~~这次比赛能做出来的最后一题。~~

---
题意：给出一个字符串，要你给这个字符串重新排序，使得字符串中相邻位置的字符在字母表中不相邻。（比如说，$b$不能和$a,c$相邻）

本人考场的思路很~~氢气~~清奇：**可以先把所有相同的字母堆到一块。** 比如，$codeforces$就可以先变成$cc\ d\ ee\ f\ oo\ r\ s$。

然后我们可以维护一个双端队列：

- 一开始队列为空的时候，就随便先放一个字母到双端队列里。

- 然后每次枚举一个字母，如果这个字母与双端队列的队头或队尾不冲突，就可以把这个字母放进去。如果没有一个字母能放进双端队列里，就说明无解。

- 最后把双端队列里面的字母依次输出即可（因为双端队列里面存储的是**一种字母**，所以我们还要事先预处理出每个字母出现的次数）

感觉思路有些迷，~~反正考场上能过就行。~~

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

deque<int> Q;

int ABS(int x){return (x>=0)?x:-x;}

char s[105];
bool ap[26];int cnt[26];

int main()
{
	int kase;scanf("%d",&kase);
	
	while(kase--)
	{
		scanf("%s",s);
		
		memset(ap,0,sizeof(ap));memset(cnt,0,sizeof(cnt));
		Q.clear();
		
		int len=strlen(s),res=0;
		
		for(int i=0;i<len;i++)
		{
			if( !ap[s[i]-'a'] ) res++;
			ap[s[i]-'a']=1,cnt[s[i]-'a']++;
		}
		
		bool fin=1;
		
		while( res )
		{
			bool flag=0;
			
			for(int i=0;i<26;i++) if( ap[i] )
			{
				if( !Q.size() ) Q.push_back(i),flag=1,ap[i]=0,res--;
				else
				{
					if( ABS( Q.front()-i )!=1 ) Q.push_front(i),flag=1,ap[i]=0,res--;
					else if( ABS( Q.back()-i )!=1 ) Q.push_back(i),flag=1,ap[i]=0,res--;
				}
			}
			
			if( !flag ){fin=0;break;}
		}
		
		if( !fin ){printf("No answer\n");continue;}
		
		while( Q.size() )
		{
			int c=Q.front();
			for(int i=1;i<=cnt[c];i++) printf("%c",c+'a');
			
			Q.pop_front();
		}
		
		printf("\n");
	}
	
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

这是一篇 Python 题解。

别的题解都使用了贪心构造的方式，但我不会做，于是只能充分发扬人类智慧，既然要求一种重排后的方案，那么我随机重新排列原序列 $ 1000 $ 次判断，如果成功生成一种合法序列则证明有解，直接输出即可。

否则答案有很大的概率为无解，直接判定为无解即可。

至于这个算法的正确性，因为数据有很大概率是随机的，打乱序列出错的概率非常小，所以这个玄学算法的正确性能得到保证。

C++ 因为某些玄学的原因是不能通过的，于是使用 Python 来做，使用了自带的 random_shuffle 函数。时间复杂度为 $ \mathcal{O}(Tn) $，自带了一个 $ 1000 $ 的常数，可以通过。

这种方式的正确性难以保证，不过有很大的概率能过本题，于是喜提本题最劣解。

代码：

```python
import random
import collections 
def check(s,n):
    for i in range(1,n):
        if abs(ord(s[i])-ord(s[i-1]))==1:
            return 1
    return 0
     
     
T=int(input())
for i in range(T):
    counter=collections.Counter(input())
    s=list(counter.keys())
    n=len(s)
    times=0
    while check(s,n) and times<=1000:
        random.shuffle(s)
        times+=1
    if check(s,n):
        print('No answer')
    else:
        print(''.join([counter[c]*c for c in s]))
```


---

## 作者：Gloaming (赞：0)

## 题目大意

让你重新排列一个字符串，使得新串中相邻的字符在字母表里面不相邻。

## 思路

根据题目的意思，是两两之间不能相邻，但没说不可以相等，就先将他们放在一起并看成一个整体。

例如`ovoqwq`在经过我们处理后就变成了`oo qq v w`。

然后对于处理后的这样的一个字符串，只需要 dfs 一下这一堆字母的排列顺序了。

事实证明，有题目中的条件限制我们的 dfs 跑不满，可以通过这一道题目。

```c++
#include <bits/stdc++.h>
using namespace std;
int countOfChar[26];
int ans[26];
bool isUsed[26];
int idx;
void ClearData(void)
{
    memset(countOfChar, 0, sizeof(countOfChar));
    memset(ans, 0, sizeof(ans));
    memset(isUsed, 0, sizeof(isUsed));
    idx = 0;
    return ;
}
void PreWork(string str)
{
    int len = str.length();
    for(int i = 0; i < len; i ++)
    {
        int cur = str[i] - 'a';        
        if(countOfChar[cur] == 0)
        {
            idx ++;
        }
        countOfChar[cur] ++;
    }
}
bool Dfs(int cur)
{
    if(cur == idx)
    {
        return true;
    }
    if(cur == 0)
    {
        for(int i = 0; i < 26; i ++)
        {
            if(countOfChar[i] > 0)
            {
                isUsed[i] = true;
                ans[cur] = i;
                if(Dfs(cur + 1) == true)
                    return true;
                ans[cur] = 0;
                isUsed[i] = false;
            }
        }
        return false;
    }
    for(int i = 0; i < 26; i ++)
    {
        if(countOfChar[i] <= 0) continue;
        if(isUsed[i] == true) continue;
        if(abs(i - ans[cur - 1]) == 1) continue;
        isUsed[i] = true;
        ans[cur] = i;
        if(Dfs(cur + 1) == true)
            return true;
        ans[cur] = 0;
        isUsed[i] = false;
    }
    return false;
}
void Printans()
{
    for(int i = 0; i < idx; i ++)
    {
        char c = ans[i] + 'a';
        for(int j = 1; j <= countOfChar[ans[i]]; j ++)
            cout << c;
    }
    cout << endl;
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while(T --)
    {
        string s;
        cin >> s;
        ClearData();
        PreWork(s);
        if(Dfs(0) == true)
            Printans();
        else cout << "No answer\n";
    }
    return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：0)

可以考虑 dfs。

我们用 num 数组，统计字符出现次数。

然后 dfs 每一种方案。

这样显然会 T ,于是考虑优化。

当当前字母可以放在这个位置时，显然将全部的当前字母都放在这个位置后面，也一定是可以的。

然后就 AC 了。

给出 dfs 部分的代码。

```cpp
void dfs(int u)
{
    if(print)   return ;
    if(u==len)
    {
        for(int i=1;i<=u;i++)    cout<<ans[i];
        puts("");
        print=true;
        return ;
    }
    for(int i=1;i<=26;i++)
        if(num[i]&&abs((int)('a'+i-1-(int)(ans[u])))!=1)
        {
            int tmp=num[i];
            for(int j=1;j<=num[i];j++)
                ans[++u]=('a'+i-1);
            num[i]=0;
            dfs(u);
            if(print)   return ;
            u-=tmp;
            num[i]=tmp;
        }
}
```


---

## 作者：Zekrom (赞：0)

刚开始我的做法是dfs+deque双端队列+剪枝    
本来过了但后来第二次评测被hackTLE了，又打了一遍    
正解  ：   
记录奇数位置odd[]（ace……），偶数位置even[]（bdf……）   
将其排序后，尝试odd+even或even+odd，可以证明这样一定能产生最优的一种结果    
上代码：dfs+deque:   
~~当然是错的~~     
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
using namespace std;
int T,ans[110],t[110],idx,len,v[110];
char ch[110];
deque<int>q;
inline int read(){
    int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
    }while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
    }return x*f;
}
bool dfs(int floor){
    if(floor==len){
        while(q.size()){
            int u=q.front();q.pop_front();
            cout<<char(u+'a'-1);
        }
        cout<<endl;
        return true;
    }
    if(floor==0){
        for(int i=1;i<=26;i++){
            if(t[i]){
                v[i]++;
                q.push_front(i);
                if(dfs(floor+1))return true;;
                q.pop_front();
                v[i]--;
            }
        }
    }
    else{
        for(int i=1;i<=26;i++){
            if(v[i]!=t[i]){
                int l=q.front(),r=q.back();
                if((i==l-1||i==l+1)&&(i==r-1||i==r+1))continue;
                else if((i==l-1||i==l+1)&&(i!=r-1&&i!=r+1)){
                    q.push_back(i);
                    v[i]++;
                    if(dfs(floor+1))return true;
                    v[i]--;
                    q.pop_back();
                }
                else if((i!=l-1&&i!=l+1)&&(i==r-1||i==r+1)){
                    q.push_front(i);
                    v[i]++;
                    if(dfs(floor+1))return true;
                    v[i]--;
                    q.pop_front();
                }
                else{
                    q.push_back(i);
                    v[i]++;
                    if(dfs(floor+1))return true;
                    v[i]--;
                    q.pop_back();
                    q.push_front(i);
                    v[i]++;
                    if(dfs(floor+1))return true;
                    v[i]--;
                    q.pop_front();
                }
            }
        }
    }
    return false;
}
int main()
{
    T=read();
    while(T--){
        cin>>(ch+1);
        len=strlen(ch+1);
        for(int i=1;i<=26;i++)v[i]=0,t[i]=0;
        for(int i=1;i<=len;i++){t[ch[i]-'a'+1]++;}
        /*for(int i=1;i<=len/2;i++){
            for(int j=1;j<=26;j++){
                if(t[j]&&j!=ans[idx]+1&&j!=ans[idx]-1){
                    t[j]--;
                    int flag=0;
                    for(int k=1;k<=26;k++){
                        if(!t[k]||k==j-1||k==j+1)continue;
                        ans[++idx]=k;
                        ans[++idx]=j; 
                        flag=1;
                        t[k]--;
                        break;
                    }
                    if(!flag){
                        goto b;
                    }
                }
            }
        } 
        if(len%2==1)
            for(int i=1;i<=26;i++){
                if(t[i]){
                    t[i]--;
                    if(ans[idx]==i-1||ans[idx]==i+1)goto b;
                    else {
                        ans[++idx]=i;
                        break;
                    }
                }
            }
        for(int i=1;i<=idx;i++)
            cout<<char(ans[i]+'a'-1);
        cout<<endl; 
        continue;
        b:printf("No answer\n");*/
        while(q.size())q.pop_front();
        if(!dfs(0))printf("No answer\n");
    }
    return 0;
}

```
    
## 正解   ：    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;
int T,ans[110],odd[110],even[110],t[110],idx,len,v[110],idx_odd,idx_even;
char ch[110];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
bool check(int t[]){
	bool flag=true; 
	for(int i=1;i<len;i++)
		flag&=(abs(t[i]-t[i+1])==1?0:1);
	return flag;
}
int main()
{
	T=read();
	while(T--){
		cin>>(ch+1);
		len=strlen(ch+1);idx_odd=idx_even=0; 
		for(int i=1;i<=len;i++){
			if((ch[i]-'a'+1)%2)
				odd[++idx_odd]=ch[i]-'a'+1;
			else
				even[++idx_even]=ch[i]-'a'+1; 
		}
		sort(odd+1,odd+idx_odd+1);
		sort(even+1,even+idx_even+1);
		for(int i=1;i<=len;i++)
			if(i<=idx_odd)
				t[i]=odd[i];
			else
				t[i]=even[i-idx_odd];
		if(check(t)){
			for(int i=1;i<=len;i++)
				cout<<(char)(t[i]+'a'-1);
			cout<<endl;
			continue; 
		}
		for(int i=1;i<=len;i++)
			if(i<=idx_even)
				t[i]=even[i];
			else t[i]=odd[i-idx_even];
		if(check(t)){
			for(int i=1;i<=len;i++)
				cout<<(char)(t[i]+'a'-1);
			cout<<endl;
			continue;
		}
		printf("No answer\n")；
	}
	return 0;
}

```



---

