# Title

## 题目描述

Vasya最近写完了一本书。现在他面临着给这本书取一个题目的问题。Vasya希望这本书的标题是含糊而神秘的，来使他的书引人注目。这就是为什么标题应该用至少k个字母中的一个来表示，而不包含任何其他的字母。此外，标题应该是一个回文，也就是说，标题从左到右，从右到左来读是一样的。
Vasya已经写下了标题的近似变体模板。你得到的标题模板由小写字母和问号组成。你的任务是用小写字母替换所有的问号，以使得结果符合上述要求。每个问号应该由一个字母替换，不允许删除字符或者添加新的字符。如果有几个合适的标题，选择字典序最小的标题，帮助Vasya尽可能早地想出标题。

## 样例 #1

### 输入

```
3
a?c
```

### 输出

```
IMPOSSIBLE
```

## 样例 #2

### 输入

```
2
a??a
```

### 输出

```
abba
```

## 样例 #3

### 输入

```
2
?b?a
```

### 输出

```
abba
```

# 题解

## 作者：ChenZQ (赞：4)

**我的第一篇题解**，求管理员通过。

首先**简化题意**：

给定一个字符串，由小写字母和问号组成，让你把每个问号都改成一个字母，并且让这个字符串是回文且字符串中的字母只能出现字母表中前 $k$ 个字母。

**思路**

很显然，第一步就是要先求出能确定的字母，比如:"a?"。

我们就可以求出这个问号一定是"a"。

为了后面方便计算，我们应该统计出每个字符和其对应的字符都是问号的数量。如:"??"，我们就将数量加一。

在遍历的同时，我们还应将出现过的字母标记出来，因为题目要求字母表前 $k$ 个字母都必须用上。

那么结合上述内容，我们就完成了整体思路的**第一步**了！

## CODE：
```
//ss表示字符串长度,t表示字符串的一半是多少，如果字符串长度是奇数,t=ss/2+1,否则t=ss/2
for(int i=0;i<t;i++)
{
	int j=ss-i-1;
	if(s[i]!=s[j])//如果两个字符不相等，有一下三种情况
	{
    //如果两个字符同为字母且不相等，直接输出IMPOSSIBLE
		if(isalpha(s[i]) && isalpha(s[j]))puts("IMPOSSIBLE"),exit(0);
		else if(s[i]=='?' && s[j]!='?') s[i]=s[j];//如果一个字符是字母且另外一个不是，说明可确定
		else if(s[i]!='?' && s[j]=='?') s[j]=s[i];  
	}
	else if(s[i]=='?' && s[j]=='?') q++;//统计出两个都是问号的对数
	if(s[i]!='?') letter[s[i]-'a']=1;
	if(s[j]!='?') letter[s[j]-'a']=1;
}
```

接下来我们来讲**第二步**。

接下来就是将这些~~可恶~~无家可归的问号都改了。

如果无家可归的问号数量小于了还每出现过的字母的数量，那么说明位置不够，输出"IMPOSSIBLE"。

由于题目要求**字典序最小**，所以越后面的问号我们越应该大，越前面的问号我们越应该让他小。

还记得我们之前统计了出现过的字母吗？

为了实现上述内容，也就是让字典序最小，我们可以从中间往前枚举字符串，每发现一个问号，就将他改成**当前未出现过的最大的字母**，然后**注意**，每次改完之后一定要标记掉，这样可以让更小的字母填入下一个问号。

在我们的一顿操作后，还有问号（我们之前填一个就标记一个，可能还会有剩余），就全改成字母"a"，让字典序最小。

时间复杂度在 $O(n)$ 级别，能通过此题。

最后一个输出，就结束啦！

## AC CODE
```
#include <bits/stdc++.h>
using namespace std;

char s[100010];
int q;
int letter[100010];
int k;

int main()
{
	scanf("%d",&k);
	scanf("%s",s);
	int ss=strlen(s);
	int t=ss/2;
	if(ss%2==1) t++; 
	for(int i=0;i<t;i++)
	{
		int j=ss-i-1;
		if(s[i]!=s[j])
		{
			if(isalpha(s[i]) && isalpha(s[j])) puts("IMPOSSIBLE"),exit(0);
			else if(s[i]=='?' && s[j]!='?') s[i]=s[j];
			else if(s[i]!='?' && s[j]=='?') s[j]=s[i];  
		}
		else if(s[i]=='?' && s[j]=='?') q++;
		if(s[i]!='?') letter[s[i]-'a']=1;
		if(s[j]!='?') letter[s[j]-'a']=1;
	}
	int cnt=0;
	for(int i=t-1;i>=0;i--)//从中间往前枚举
	{
		if(s[i]=='?')
		{
			int id=-1;
			for(int i=k-1;i>=0;i--)
			{
				if(!letter[i])
				{
					id=i;break;
				}
			}
			if(id==-1) break;
			s[i]=id+'a';
			s[ss-i-1]=id+'a';//改问号&改成字母
			letter[id]=1;
		}
	}
	for(int i=0;i<k;i++)
	{
		if(!letter[i])
		{
			puts("IMPOSSIBLE");
			exit(0);
		}
	}
	for(int i=0;i<t;i++)
	{
		if(s[i]=='?')
		{
			s[i]='a';
			s[ss-i-1]='a';//将剩下的字母全改成"a"
		}
	}
	printf("%s",s);
}
```

创作不易，给个赞吧。

---

## 作者：灵光一闪 (赞：4)

emming……，这道题卡了我好久，然后居然发现IMPOSSIBLE打成了IMPOSSBLE ~~（英文渣~~ 23333

**~~Ctrl+c  Ctrl+v大fa好~~**


讲解全在代码里
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<set>
using namespace std;
int k;
string s;
set <char> c;
void solve()
{
    cin>>k>>s;
    for(int i=0;i<k;i++)
        c.insert('a'+i);//压进去
    for(int i=0;i<s.size();i++)
        c.erase(s[i]);
    int cnt=0;
    for(int i=0;i<(s.size()+1)/2;i++)
    {
        int j=s.size()-1-i;
        if(s[i]=='?'&&s[j]=='?')
        {
            cnt++;
            continue;
        }
        if(s[i]=='?')           //互相补充，如果不一样就说明IMPOSSIBLE！
            s[i]=s[j];
        if(s[j]=='?')
            s[j]=s[i];
        if(s[i]!=s[j])
        {
            puts("IMPOSSIBLE");
            return;
        }
    }
    if(cnt<c.size())            //超出总长度了！
    {
        puts("IMPOSSIBLE");
        return;
    }
    for(int i=0;i<(s.size()+1)/2;i++)
    {
        int j=s.size()-1-i;
        if(s[i]=='?'&&s[j]=='?')//if语句的解释：不到万不得已，不放除‘a’以外的字母（字典序最小嘛）
        {
            if(cnt==c.size())
                s[i]=s[j]=*c.begin(),c.erase(c.begin()),cnt--;
            else
                s[i]=s[j]='a',cnt--;
        }
    }
    cout<<s;
    return;
}
int main()
{
    solve();
    return 0;
}
```

---

## 作者：infinities (赞：3)

一道比较水但是细节比较坑的题。

这里提供一种比较清晰的方法。

由于题目要求是回文串，所以只用考虑字符串的一半，剩下的一半对应着就好。

刚开始先扫一遍，将前后都是"?"的地方计数，以下问号对数记为 $T$，然后如果有一侧是"?"另一侧是字母的直接赋值对应，注意如果两侧都是字母且不相同直接输出，结束程序。

然后记录下已经有的字符，特判 $k$ 以内还没有的字符数 $Q$ 是否大于问号对数。

再然后再扫一遍，贪心把前 $T-Q$ 组问号都搞成"a"，然后剩下的赋值为还没有出现的下一个字母。

这样就既满足了字典序的要求又特判完了所有特殊情况。

但是据说CF是炸的并且洛谷也无法抓取记录？

所以代码没法评测（不过测样例没错）。

这里代码贴一下仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;

int k,t;
string s;
int a[1222];
int cou[1222],cnt;

signed main(){
    cin>>k;
    cin>>s;
    
    int l=s.size();

    for(int i=0;i<s.size();i++){
        if(s[i]!='?'&&(s[i]-'a'+1)>k){cout<<"IMPOSSIBLE";return 0;}//特判1

        if(s[l-i-1]!=s[i]&&s[i]!='?'&&s[l-i-1]!='?'){cout<<"IMPOSSIBLE";return 0;}//特判2

        if(s[l-i-1]!='?'&&s[i]!='?')a[s[i]-'a'+1]++;//处理一下然后记录
        
        if(s[i]=='?'&&s[l-i-1]!='?')s[i]=s[l-i-1],a[s[i]-'a'+1]++;
        else
        if(s[l-i-1]=='?'&&s[i]!='?')s[l-i-1]=s[i];//以上就是刚开始的瞎搞
        else
        if(s[i]=='?'&&s[l-i-1]=='?')t++;//记录对数
    }
    
    for(int i=1;i<=k;i++){
        if(a[i]==0)cou[++cnt]=i;
    }
    t=ceil((double)t/2);//因为会数重这里除以1个2
    if(t<cnt){cout<<"IMPOSSIBLE";return 0;}//特判3
    
    int now=0;
    
    for(int i=0;i<s.size();i++){
        if(s[i]=='?'&&s[l-i-1]=='?'){
            if(t>cnt)s[i]='a',s[l-i-1]='a';else//贪心
            
            s[i]='a'+cou[++now]-1,s[l-i-1]='a'+cou[now]-1;//贪心2
            
            t--;
        }
    }
    cout<<s;//输出
}
```

---

## 作者：wkjwkj (赞：2)

[可能更好的阅读体验](https://mywkj.github.io/2020/03/28/cf59c-ti-jie/)

[**原题链接**](https://codeforces.ml/problemset/problem/59/C)

# $ first$ $step: $

- 首先注意到题目中有一个重要的性质:那就是每一个标题都是回文的，那么我们就可以利用这个性质把能够确定的字母先填上。例如样例三就可以直接通过这个性质解决。

- 其次，题目中要求标题的字典序最小，那么我们就有了一个类似于贪心的策略，遇到‘？’就尽可能的填上’a'（当然必须要保证标题中有前k个字母出现，例如样例二）。

- 在上述步骤完成后，还要在检验一遍标题中是否有前k个字母出现。

- 值得一提的是，输入的标题内可能全部是‘？’，~~尽管这对我们的算法没有影响~~，比如

- ```php
  输入:
  2
  ??????
  输出:
  aabbaa
  输入:
  5
  ????
  输出:
  IMPOSSIBLE
  ```


#  $second $  $ step: $​

AC代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
bool use[30];
int many=0;
char s[200];
int main()
{
	int k;
	scanf("%d",&k);
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
	{
		if(s[len-i+1]=='?'&&s[i]!='?')s[len-i+1]=s[i];
		else if(s[i]=='?'&&s[len-i+1]!='?')s[i]=s[len-i+1];
		else if(s[len-i+1]!=s[i]){
			puts("IMPOSSIBLE");
			//printf("%d",i);
			return 0; 
		}
		if(s[i]!='?')use[s[i]-'a'+1]=true;
		else many++;
	}
	many=ceil(many*1.0/2);
	//printf("%d\n",many);
	int cnt=0;
	for(int i=1;i<=k;i++)
	  if(use[i]==false)cnt++;
	for(int i=1;i<=len;i++)
	{
		if(s[i]=='?'){
			if(many>cnt&&use[1]==true){
			s[i]=s[len-i+1]='a',many--;
			continue;	
			}
			int who=-1;
			for(int j=1;j<=k;j++)
			  if(use[j]==false){
			  	who=j;
			  	use[j]=true;
			  	break;
			  }
			s[len-i+1]=s[i]=who+'a'-1;
			many--;
			cnt--;
		}
	}	
	for(int i=1;i<=k;i++)
	  if(use[i]==false){
	  	puts("IMPOSSIBLE");
	  	return 0;
	  }
	for(int i=1;i<=len;i++)
	  printf("%c",s[i]);
}
```



---

## 作者：rain_dew (赞：0)

这是一道模拟题，我用的是一个**字符数组**的方法。

## 思路：
1. 先判断初始告诉我们的字符的有无，有就给判断字符打上标记。

2. 然后从中间劈开，从中间往两边寻找，会出现以下的四种情况:

- 两边数组**不一样**，直接输出 ```IMPOSSIBLE```
 后退出。

- 两边数组**一样**（不是$?$），不用管，继续寻找。

- 有**一边**是$?$，把它（$?$）变为与其对称的字母。

- **两边**都是 $?$，分析标记，寻找最大的未出现的字母。否则输出最小字符 $a$。
 
3. 最后再去判断是否所有的字母全部出现，最后输出答案。

------------
## 为什么要从中间向两边寻找？
此题要求我们字典序最小，分到最后会出现两种情况：

- 要么有字符没有用，分到未出现的字母的最小字母。

- 要么没有字符没有使用，我们就可以分到最小字母 $a$。

如果我们从两边向中间寻找，我们无法判断是否为最小的字典序，导致我们需要加入特判以及记录双问号的情况。

当我们寻找完后，**还需要再次的判断问号需要所填的字母**。

因此，综上所述，从中间开始寻找是比较方便的。

## 附上朴实的AC代码：

```cpp
// LUOGU_RID: 93834973
#include <bits/stdc++.h>
using namespace std;
int n;
char ch[101];
bool p[30];
int main()
{
	scanf("%d",&n);
	cin>>ch+1;
	int len=strlen(ch+1);
	for (int i=1;i<=len;i++)
		if (ch[i]!='?')
			p[ch[i]-96]=1;
	int l,r;
	if (len%2)
		l=r=len/2+1;
	else
		l=len/2,r=len/2+1;
	while (l>=1)
	{
		//cout<<l<<' '<<r<<endl;
		if (ch[l]!=ch[r] && ch[l]!='?' && ch[r]!='?')
		{
			printf("IMPOSSIBLE");
			return 0;
		}
		if (ch[l]==ch[r] && ch[l]!='?')
		{
			l--,r++;
			continue;
		}
		if (ch[l]==ch[r] && ch[l]=='?')
		{
			bool flag=0;
			for (int i=n;i>=1;i--)
				if (p[i]==0)
				{
					ch[l]=ch[r]=char(i+96);
					p[i]=1;
					flag=1;
					break;
				}
			if (flag==0)
				ch[l]=ch[r]='a';
			l--,r++;
			continue;
		}
		if (ch[l]=='?')
		{
			ch[l]=ch[r];
			l--,r++;
			continue;
		}
		if (ch[r]=='?')
		{
			ch[r]=ch[l];
			l--,r++;
		}
	}
	for (int i=1;i<=n;i++)
		if (p[i]==0)
		{
			printf("IMPOSSIBLE");
			return 0;
		}
	cout<<ch+1;
	return 0;
}
```

---

## 作者：_wjr_ (赞：0)

一道很好的题，就是翻译压在一起，很难看，坑也有点多。

[题目传送门](https://www.luogu.com.cn/problem/CF59C)

## 题目大意

给定一个数字 $k$ 与一个字符串 $s$，问能否只用前 $k$ 个字母，且每个字母都要用，并将 $s$ 中所有问号替换成字母，使得最终的字符串是一个回文串。若能，输出字典序最小的答案，否则输出 `IMPOSSIBLE`。

## 题目思路

既然给出的是一个带有问号的字符串，并且最终我们需要得到一个回文串，那么，假设 $s$ 由 $x$ 个字符组成，那么，对于读入进来的 $s_i$ 与 $s_{x - i + 1}$，进行一个初步处理，我们不妨分为以下情况：

1.  若 $s_i$ 与 $s_{x - i + 1}$ 均为字母，且它们不是同一个字母，那么此时直接输出 `IMPOSSIBLE` 结束程序。
2. 若 $s_i$ 与 $s_{x - i + 1}$ 均为字母，且它们是同一个字母，那么不用管它们，到后面一起判定是否符合要求。
3. 若 $s_i$ 与 $s_{x - i + 1}$ 中有一个是 `?`，另一个是字母，那么把 `?` 替换成该字母。
4. 若 $s_i$ 与 $s_{x - i + 1}$ 均为问号，那么留到下一步处理。

这时候，如果 $s$ 字符串仍符合要求，那么它就只能是由 `?` 与字母组成的字符串了。目前的目标就是要把所有 `?` 替换为字母。

我们不妨设现在一共还有 $m$ 组问号，并且在前 $k$ 个字母中还有 $n$ 个字母（$p_1 , p_2 , \cdots, p_n$）没有用。由于要求字典序最小，这时我们只需要把前面 $m - n$ 组 `?` 变成 `a` ，其余的依次换成 $p_1 , p_2 , \cdots, p_n$ 就可以了。

最后，我们便做完这道题了……

吗？

很明显，并不是。

题目中要求，我们要用前 $k$ 个字母，当一开始的时候便有第 $k+1$ 甚至更往后的字母。或者，在把 `?` 替换成字母的时候，已经没有足够的问号使得前 $k$ 个字母均出现一次，这时便需要输出 `IMPOSSIBLE`。

于是，题目的思路就有了。

## AC code

```cpp
#include<bits/stdc++.h>

using namespace std;

bool flag[110];

int main()
{
    int k, cnt = 0;//有多少组问号
    string s;
    cin >> k >> s;
    int count = k;//还有多少个字母没有出现，初值要设为k
    for (int i = 0; i <= (s.length() - 1) / 2; i++)
    {
        int j = s.length() - 1 - i;
        if (s[i] != s[j] && s[i] != '?' && s[j] != '?')
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
        else if (s[i] == '?' && s[j] != '?') 
        {
            s[i] = s[j];
            if (flag[s[i] - 'a' + 1] == false) count--;
            flag[s[j] - 'a' + 1] = true;
        }
        else if (s[j] == '?' && s[i] != '?')
        {
            s[j] = s[i];
            if (flag[s[i] - 'a' + 1] == false) count--;
            flag[s[i] - 'a' + 1] = true;
        }
        else if (s[i] == s[j] && 'a' <= s[i] && s[i] <= 'z') 
        {
            if (flag[s[i] - 'a' + 1] == false) count--;
            flag[s[i] - 'a' + 1] = true;
        }
        else if (s[i] == '?' && s[j] == '?') cnt++;
    }//将目前能处理的先行处理
    for (int i = 0; i <= (s.length() - 1) / 2; i++)
    {
        if (s[i] == '?')
        {
            if (cnt > count) 
            {
                s[i] = 'a';
                s[s.length() - i - 1] = 'a';
                cnt--;
            }
            else
            {
                cnt--;
                count--;
                for (int j = 1; j <= k; j++)
                    if (flag[j] == false)
                    {
                        flag[j] = true;
                        s[i] = char(j + int('a') - 1);
                        s[s.length() - i - 1] = char(j + int('a') - 1);
                        break;
                    }
            }
        }
    }//将问号替换成字母
    bool check = true;
    for (int i = 1; i <= k; i++)
        if (flag[i] == false) check = false;
    if (!check) 
    {
        cout << "IMPOSSIBLE";
        return 0;
    }//如果不是所有字母都出现，输出IMPOSSIBLE
    else
    {
        for (int i = k + 1; i <= 26; i++)
            if (flag[i])
            {
                cout << "IMPOSSIBLE";
                return 0;
            }//如果有其它不应该出现的字母，输出IMPOSSIBLE
        cout << s;//如果满足要求，输出这个字符串
    }
    return 0;
}
```

完结撒花！

---

## 作者：sunyizhe (赞：0)

欢迎各位dalao来看本蒟蒻的题解！

[题目传送门](https://www.luogu.com.cn/problem/CF59C)

此处鸣谢大佬 [@infinities](https://www.luogu.com.cn/user/209547)
## 一、思路
1. 输入, $k$ 为所用字母数，$s$ 为字符串。

2. 先从两边到中间扫一边字符串，将能确定的"?"处填好，变量 $cnt$ 记录问号对，同时初次判断是否 IMPOSSIBLE。(Code 6~23 行)
 
3. 变量 $cnt1$ 是否能用到所有字母，第二次判断是否 IMPOSSIBLE。(Code 24~29 行)

4. 按照题意补全字符串，最后输出。(Code 30~67 行)
## 二、代码
程序中上述没有讲的都在代码里注释了，请放心食用。
```cpp
#include <bits/stdc++.h>
using namespace std;
bool pd[30];//判断用过字母
int main()
{
        string s;
        int k,len;
        cin>>k>>s;
        len=s.size();//字符串长度
        int cnt=0,cnt1=0;
        for(int i=0;i<len;i++)
        {
            int j=len-i-1;//取对称位置
            if(s[j]!='?'&&s[i]!='?'&&s[i]!=s[j])//不符合要求
            {
                cout<<"IMPOSSIBLE"<<endl;
                return 0;
            }
            if(s[i]=='?'&&s[j]!='?')s[i]=s[j],pd[s[j]-'a'+1]=true;
            if(s[i]!='?'&&s[j]=='?')s[j]=s[i],pd[s[i]-'a'+1]=true;//一边有问号
            if(s[i]!='?'&&s[j]!='?')pd[s[i]-'a'+1]=true;//都不是问号
            if(s[i]=='?'&&s[j]=='?')cnt++;//都是问号
        }
        for(int i=1;i<=k;i++)if(!pd[i])cnt1++;//统计未用到字母
        if(cnt>cnt1+1)//无法全部用到字母
        {
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
        for(int i=0;i<len;i++)
        {
            int j=len-i-1;
            if(s[i]=='?')//找到问号
            {
                bool flag=false;
                for(int x=1;x<=k;x++)
                    if(!pd[x])//找到第一个未使用字母
                    {
                        s[i]=s[j]=x-1+'a';
                        pd[x]=true;
                        flag=true;
                        break;
                    }
                if(flag==false)s[i]='a';//都用过了
            }	
        }
        cout<<s<<endl;
        return 0;
}
```


---

## 作者：abensyl (赞：0)

### 原题：[原题传送门](https://www.luogu.com.cn/problem/CF59C)

## 思路：

这题就是个~~模拟~~，勉强算个双指针。

- 定义两个指针 $i$ 和 $j$，让他们两从前后出发，同时向中间走，如果 $s_i$ 或 $s_j$ 中有且仅有一个为问号，直接赋值对应。

- 再然后从中间往两边再扫一遍，将所有问好赋值为还没有出现的下一个字母，当还没出现的下一个字母只剩一个时，将剩下的问号全赋值为它（上述所有赋值操作都是对应赋值）。

- 检查如果从 $1$ 到 $k$ 这 $k$ 个字母是否都用了，若是，输出字符串，否则，输出 `IMPOSSIBLE`。

- &#9733; 华丽结束 &#9733;。

贴心服务：如果没看懂可以看注释都在代码里哦！

## 代码（本人蒟蒻，码力严重不足）：

```cpp
#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define all(a) (a).begin(), (a).end()
#define sz(x) (ll) x.size()

using namespace std;

ll c[30];

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  ll n, i;
  cin >> n;
  string s;
  cin >> s;
  ll l = s.length();
  for (i = 0; i < l / 2; ++i)  //循环l/2次，相当于双指针（i就是i，j=l-i-1）
    if (s[i] == '?') {  //如果s[i]和s[j]其中一个是问号，将问号改为对方
      if (s[l - i - 1] != '?') {
        s[i] = s[l - i - 1];
        c[(int)s[i] - 96] = 1;
      }
    } else {
      if (s[l - i - 1] == '?') {
        s[l - i - 1] = s[i];
        c[(int)s[i] - 96] = 1;
      } else if (s[i] != s[l - i - 1])
        break;
      else
        c[(int)s[i] - 96] = 1;
    }
  if (i < l / 2)
    cout << "IMPOSSIBLE";  //如果i仍然小于l/2说明无解
  else {
    ll j = n;
    if (l % 2) {  //特殊处理l为奇数时的s[l/2]
      if (s[l / 2] == '?') {
        for (; j > 1; --j)
          if (!c[j]) {
            s[l / 2] = (char)(j + 96);
            break;
          }
        if (j == 1) {
          s[l / 2] = 'a';
          c[1] = 1;
        }
      }
      c[(int)s[l / 2] - 96] = 1;
    }
    for (i = (l / 2) - 1; i >= 0; --i)
      if (s[i] == '?') {  //如果s[i]等于问号，就将其和s[l-i-1]设为j
        while (c[j] && j > 1) j--;  //重设j
        s[i] = (char)(j + 96);
        s[l - i - 1] = (char)(j + 96);
        c[j] = 1;
      }
    for (i = 1; i <= n; i++)
      if (!c[i]) break; //如果c[i]为零，说明IMPOSSIBLE
    if (i <= n)
      cout << "IMPOSSIBLE";
    else
      cout << s; //否则输出字符串
  }
  return 0; //华丽结束
}

```

AC记录：[AC记录](https://www.luogu.com.cn/record/82621213)。

各位看官大佬，点个赞呗！

---

## 作者：fuzhelin1984 (赞：0)

题面讲解足够清晰了，这题可以算作是一道较为复杂的大模拟。我的作法是在一开始先将可以确定的部分填出，例如 'a' 和 '? ' ，我们可以把两个都统一为 ‘a’ 。对于两个相对的 ‘?’,我选择留到最后统一处理，由两头向中间优先用字典序小的字母填写，这样也能保证字典序最小。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200;
bool syy[N],flg = false;
int n, tot = 26;
string s;
int main()
{
	cin >> n >> s;
	int len = s.length();
	memset(syy,false,sizeof(syy));
	if(n*2 > len+1) 
	{
		cout<<"IMPOSSIBLE";
		return 0;
	}
	for(int i = 0;i <= (len+1)/2-1;++i)
	{
		if(i == len-i-1) 
		{
			if(s[i] != '?') syy[s[i]-'a' + 1] = true;
			continue;
		}	
		if(s[i] != '?')
		{
			if(s[len-i-1] != '?' && s[len-i-1] != s[i]) 
			{
				cout<<"IMPOSSIBLE";
				return 0;
			}
			if(s[len-i-1] == '?')
			{
				s[len-i-1] = s[i];
				syy[s[i]-'a' + 1] = true;
			}
			if(s[len-i-1] == s[i])
			{
				syy[s[i]-'a' + 1] = true;
			}
		} 
		if(s[i] == '?')
		{
			if(s[len-i-1]=='?') continue;
			if(s[len-i-1]!='?')
			{
				s[i] = s[len-i-1];
				syy[s[i]-'a' + 1] = true;
			}
		}
	}
	for(int i = (len+1)/2-1;i >= 0;--i)
	{
		if(s[i] == '?' && s[len-i-1] == '?') 
		{
			if(flg)
			{
				s[i] = 'a';
				s[len-i-1] = 'a';
			}
			else
			{
				for(int j = n;j >= 1;--j)
				{
					if(!syy[j])
					{
						tot = j;
						syy[j] = true;
						s[i] = j +'a' - 1;
						s[len-i-1] = j +'a' - 1;
						if(j == 1) flg = true;
						break;
					}
				}
			}
		}
	}
	for(int i = 1; i <= n; i++)
		if(syy[i] == false)
		{
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	for(int i = (len+1)/2-1;i >= 0;--i)
	{
		if(s[i] == '?' && s[len-i-1] == '?') 
		{
			s[i] = 'a';
			s[len-i-1] = 'a';
		}
	}
	cout<<s<< endl;
	return 0;
}
```


---

## 作者：wangyixuan_s_father (赞：0)

这题~~不仅耗肝，还耗肾~~要码一堆代码
#### 解题思路
首先，我们要分析题目：题目本质就是让我们找问号配对凑出 $k$ 个字母。

因为题目要求回文串，所以循环只用转一半，另一半对应就好。
遍历字符串的一半，找出成对的问号数目记为 $f$，位置存在数组 $sv$ 里,同时记录已有字母并判断IMPOSSIBLE。
然后从 $z$ 向 $a$ 找，同时以倒序在 $sv$ 中找位置安排没出现的字符。
所有字符都安排完之后，如果还有问号对，就全部填 $a$。

不说了，上代码：
```cpp
#include<bits/stdc++.h>//万能头万岁！
using namespace std;
int cnt[27],f,sv[101];
int main()
{
	int k,tmp=1,sum=1,nd=0;
	cin>>k;
	string s;
	cin>>s;
	if(k==1&&s.size()==1)//首先特判单字符
	{
		if(s[0]=='a'||s[0]=='?')
		{
			cout<<"a";
			return 0;
		}
		else
		{
			cout<<"IMPOSSIBLE";//忌小写
			return 0;
		}
	}
	for(int i=0;i<s.size()/2;i++)//遍历字符串（半个）
	{
		int j=s.size()-i-1;//对应位
		if(s[i]-96>k||s[j]-96>k)//判断越界（其实不用）
		{
			cout<<"IMPOSSIBLE";
			return 0;
		}
		if(s[i]==s[j])
		{
			if(s[i]=='?')//处理问号对
			{
				f++;
				sv[tmp]=i;
				sv[++tmp]=j;
				tmp++;
			}
			else cnt[s[i]-96]++;//记录出现过的字符
		}
		else
		{
			if(s[i]>96&&s[j]>96)//判断冲突
			{
				cout<<"IMPOSSIBLE";
				return 0;
			}
			else
			{
				s[i]=max(s[i],s[j]);//改字符并记录出现
				s[j]=s[i];
				cnt[s[i]-96]++;
			}
		}
	}
	if(s.size()%2>0&&s[s.size()/2]=='?')//判断中心问号
	{
		sv[tmp++]=s.size()/2;
	}
	tmp--;
	for(int i=k;i>=1;i--)//倒序遍历前k个字符出现次数
	{
		if(cnt[i]==0)
		{
			f--;
			if(f<0)//如果缺字母太多，补不齐，就不行
			{
				cout<<"IMPOSSIBLE";
				return 0;
			}
			if(tmp%2!=0)//首先用掉中心问号（如果有的话）
			{
				s[sv[tmp--]]=i+96;
				continue; 
			}
			s[sv[tmp--]]=i+96;
			s[sv[tmp--]]=i+96;
		}
	}
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='?')cout<<"a";//用a填所有问号
		else cout<<s[i];
	}
	return 0;//求管理大大通过
}
```


---

## 作者：Allanljx (赞：0)

## 题意
给一个字符串，这个字符串中只包含小写字母和 $?$。现在让你将每个问号都替换成小写字母，并且使这个字符串满足下面两个条件：

- 这个字符串是回文的
- 前 $k$ 个小写字母都必须出现过（$k$ 题目中会给出）

如果不存在输出```IMPOSSIBLE```

## 思路
模拟，当有一组对应的位置上都是字母且不一样时就不能满足回文，所以不行。当有一组有一个位置确定时另一个位置也就相当于确定了。然后再将没有确定的位置从后向前填没有填过的字母（字母也从后向前填）。如果在填完所有字母后还有空余的位置上就都填上 $a$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char c[105];
int b[30],l,x;
signed main()
{
	cin>>x;
	cin>>(c+1);
	l=strlen(c+1);
	for(int i=1,j=l;i<=(l+1)/2;i++,j--)
	{
		if(c[i]=='?'&&c[j]=='?') continue;//无法确定
		if(c[i]==c[j]) b[c[i]-'a']++;//统计字母出现的次数
		if(c[i]=='?') c[i]=c[j],b[c[j]-'a']++;//一组字母必须对应
		if(c[j]=='?') c[j]=c[i],b[c[i]-'a']++;//一组字母必须对应
		if(c[i]!='?'&&c[j]!='?'&&c[i]!=c[j]||c[j]-'a'>=x)//不可能变为回文串
		{
			cout<<"IMPOSSIBLE\n";
			return 0;
		}
	}
	for(int i=x-1;i>=0;i--)//从后往前填没有填过的字符
	{
		if(b[i]) continue;//这个字母已经有了
		for(int j=(l+1)/2,k=(l+1)/2+bool(l%2==0);j>=1;j--,k++)//填字母
		{
			if(c[j]=='?')
			{
				c[j]=c[k]=char(i+'a');//填字母
				b[i]=1;
				break;
			}
		}
	}
	for(int i=0;i<x;i++)
	{
		if(!b[i])//如果还有字母没填进去
		{
			cout<<"IMPOSSIBLE\n";
			return 0;
		}
	}
	for(int i=(l+1)/2,j=(l+1)/2+bool(l%2==0);i>=1;i--,j++)//还有可以填字母的地方
	{
		if(c[i]=='?') c[i]=c[j]='a';//字典序最小
	}
	for(int i=1;i<=l;i++) cout<<c[i];
}
```

---

## 作者：vegetable_king (赞：0)

在[博客](https://yjh965.github.io/post/cf59c-title-ti-jie/)食用更佳。

# 思路
一道较水的模拟题。

首先，我们输入 $k$ 和字符串后，设置一个变量 $wh$ 代表不确定的问号对的数量，设置一个 `bool` 类型的数组 $vis_i$ 标记每个字母有没有出现过，然后用一个循环从字符串的两端向中间搜起，（代码里有）然后，如果搜到的两个字符不相同且不是 `?`，直接输出 `IMPOSSIBLE`。如果两个字符一个是 `?`，一个是字母，就把 `?` 这个字符设置成字母，顺便用 `vis[i] = 1` 标记这个字母出现过。如果两个字符都是相同的字母，也要标记哦！如果两个字符都是 `?`，则 ` wh ++ `，统计问号对出现的次数。

这样先把字符串能填的都填上，再统计一下有多少个字母没有出现过。

```cpp
int xy = 0;
for (int i = 0;i < k;i ++) xy += !vis[i];
```

对于第 $0$ 到第 $k$ 个小写字母，每有一个没出现过，$xy$ 就加 $1$。

我们又想到一种情况，如果可以用来填字母的问号对比没出现过的字母数还少，那肯定做不到让所有的字母起码出现一次，所以如果出现这种情况，也可以直接输出 `IMPOSSIBLE` 了！

按照刚刚的定义，还有 $wh$ 个不确定的问号对，和 $xy$ 个没出现的字母，则有 $wh-xy$ 个空闲的问号对。

根据贪心思想，我们要把空闲的问号对都填上 `a`，再根据字典序的排序方法，我们应该在问号对上面优先填上 `a`，再填上需要的字母。假如 $k$ 为 $3$，而字符串为 `a??????a`，则应输出 `aabccbaa`。这就可以保证 `a`，`b`，`c` 各出现至少一次而且字典序最小。

那要在什么情况下再填需要的字母呢？当然要在没有空闲问号对的情况下填了！

这样，问题就迎刃而解了！
# 代码
```cpp
#include <iostream>
#include <string>

using namespace std;

string s;
int n, wh, xy;
char yt;
bool vis[26];
int main(){
	cin >> n >> s;
	for (int l = 0, r = s.size() - 1;!(r < l);r --, l ++){ // 定义左点和右点并向中间移动
		if (s[l] != '?' && s[r] != '?' && s[l] != s[r]){ // 都是字母且不相等
			cout << "IMPOSSIBLE";
			return 0;
		}
		if (s[l] == s[r]){ // 相等
			if (s[l] == '?') wh ++; // 都是问号则统计问号对
			else vis[s[l] - 'a'] = 1; // 都是字母则统计字母
		}
		else { // 不相等
			if (s[l] == '?') s[l] = s[r]; // 左问号右字母
			else s[r] = s[l]; // 相反
			vis[s[l] - 'a'] = 1; // 统计字母
		}
	}
	for (int i = 0;i < n;i ++) xy += !vis[i]; // 统计未出现的字母
	if (wh < xy){ // 问号对不够
		cout << "IMPOSSIBLE";
		return 0;
	}
	for (int l = 0, r = s.size() - 1;!(r < l);r --, l ++){
		yt = 'a'; // 先设置为 'a'
		if (s[l] == '?'){ // 发现问号对
			if (wh <= xy){ // 不能填 'a' 了
				int i;
				for (i = 0;i < n && vis[i];i ++) yt ++; // 找到第一个没出现过的字母
				vis[i] = 1; // 标记为出现过
			}
			else wh --; // 可以填 'a'，空闲的问号对 - 1
			s[l] = s[r] = yt; // 把两个问号设置成字母
		}
	}
	cout << s; // 输出字符串
}
```

---

