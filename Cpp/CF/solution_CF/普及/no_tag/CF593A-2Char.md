# 2Char

## 题目描述

Andrew often reads articles in his favorite magazine 2Char. The main feature of these articles is that each of them uses at most two distinct letters. Andrew decided to send an article to the magazine, but as he hasn't written any article, he just decided to take a random one from magazine 26Char. However, before sending it to the magazine 2Char, he needs to adapt the text to the format of the journal. To do so, he removes some words from the chosen article, in such a way that the remaining text can be written using no more than two distinct letters.

Since the payment depends from the number of non-space characters in the article, Andrew wants to keep the words with the maximum total length.

## 说明/提示

In the first sample the optimal way to choose words is {'abb', 'aaa', 'bbb'}.

In the second sample the word 'cdecdecdecdecdecde' consists of three distinct letters, and thus cannot be used in the article. The optimal answer is {'a', 'a', 'aaaa'}.

## 样例 #1

### 输入

```
4
abb
cacc
aaa
bbb
```

### 输出

```
9```

## 样例 #2

### 输入

```
5
a
a
bcbcb
cdecdecdecdecdecde
aaaa
```

### 输出

```
6```

# 题解

## 作者：Ninelife_Cat (赞：2)

其实不用预处理直接暴力就能过。

枚举两个字符，每次扫一遍所有的字符串，如果当前字符串符合条件就加上它的长度。

最后取最大值即可。

$Code$ :

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[101];
int n,ans;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(char i='a';i<='z';i++)
		for(char j=i+1;j<='z';j++)//枚举字符
		{
			int sum=0;
			for(int k=1;k<=n;k++)
			{
				bool f=false;
				for(int l=0;l<a[k].length();l++)
					if(a[k][l]!=i&&a[k][l]!=j) {f=true;break;}//判断该字符串是否符合条件
				if(!f) sum+=a[k].length();
			}
			ans=max(ans,sum);//取最大值
		}
	cout<<ans;
	return 0;
}

---

## 作者：Lucifer_Bartholomew (赞：2)

# ~~dp~~
类似背包，对于每一个字符串，分取或者不取两种情况讨论。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int k1[26][26],s[120][26],l1[120],l2[120];
char s1[120][1200];
int main() 
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    	scanf("%s",s1[i]);
    for(int i=1;i<=n;++i)
	{
    	l1[i]=strlen(s1[i]);
    	sort(s1[i],s1[i]+l1[i]);
    	l2[i]=unique(s1[i],s1[i]+l1[i])-s1[i];//将字符串简化到每个出现的字符只保留一个
    	if(l2[i]==1)s[i][s1[i][0]-'a']=1;
    	if(l2[i]==2)s[i][s1[i][0]-'a']=s[i][s1[i][1]-'a']=1;
    }
    int ans=-1;
    for(int i=0;i<26;++i)//dp（背包）
	{
    	for(int j=0;j<26;++j)
		{
    		for(int k=1;k<=n;++k)
    			if(l2[k]==2&&s[k][i]==1&&s[k][j]==1&&i!=j)k1[i][j]+=l1[k];
    			else if(l2[k]==1&&(s[k][i]==1||s[k][j]==1))k1[i][j]+=l1[k];
    		ans=max(ans,k1[i][j]);
    	}
    }
    printf("%d\n",ans);
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：Iron_Heart (赞：1)

## 思路

暴力枚举两个小写字母，然后遍历一遍所有单词。

如果当前遍历到的单词只由枚举到的两个小写字母组成，则将单词长度累加至 `lensum`。

最后所有 `lensum` 取最大值，输出即可。

复杂度约为 $O(26^2 \times n)$，因为 $n$ 最大只有 $100$，所以可以稳过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef set<char>::iterator scit;

int n, ans;
string sa[105];
map< string, set<char> > m;

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> sa[i];
        for (int j = 0; j < sa[i].size(); ++j) {
            m[sa[i]].insert(sa[i][j]);
        }
    }
    for (char a = 'a'; a < 'z'; ++a) {
        for (char b = a + 1; b <= 'z'; ++b) {
            int lensum = 0;
            for (int i = 0; i < n; ++i) {
                bool flag = 1;
                string s = sa[i];
                for (scit j = m[s].begin(); j != m[s].end(); ++j) {
                    char c = *j;
                    if (c != a && c != b) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    lensum += s.size();
                }
            }
            ans = max(ans, lensum);
        }
    }
    cout << ans;
    return 0;
}
```


---

## 作者：山田リョウ (赞：0)

强烈怀疑是恶评。。。真实难度是红题。。。

首先我们预处理出那些字符串包含的字符种类不超过 $2$，并把它包含哪些字符，存下来。因为超过 $2$ 的是没用的，无论选哪两个字符也不可能使其只包含这两个字符。

然后我们就暴力枚举这两个字符是什么，再用之前预处理出来的信息暴力判断就好了。。。

[代码](https://www.luogu.com.cn/paste/nmp751gk) 写的比较丑，见谅。

---

## 作者：MuYC (赞：0)

#### 前言(feihua)

凭什么这道题被评成了蓝题？

~~恶意评分~~

这道直接无脑暴力O($\frac{26^3}{2} * n$)即可。

相信您可以10分钟码完然后一遍$AC$，这道题也木有细节。

#### 具体做法

因为字母只有26种，组合起来只有$\frac{26*26}{2}$种，直接暴力枚举即可。然后我们需要判断哪一些字符串仅仅含有这两个字符（可以只有其中一个字符），所以想到预处理出每一个串含有哪一些字符。用桶来记录即可。

这道题代码比较短，如果觉得我上面讲的不够清楚的话可以看代码，写了注释。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char a[101][1005];
int book[101][28],Maxlen = -1;
int main()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];//读入一个字符串
		int len = strlen(a[i]);
		for(int j = 0 ; j < len ; j ++)
			book[i][a[i][j] - 'a' + 1] = 1;//统计字符串i含有哪一些字符
	}
	for(int i = 1 ; i <= 26 ; i ++)
	{
		for(int j = i + 1 ; j <= 26 ; j ++)//枚举两个字符
		{
			int ans = 0;
			for(int k = 1 ; k <= n ; k ++)//判断是否记录入答案
			{
				int flag = 1;
				for(int l = 1 ; l <= 26 ; l ++)//枚举26个字符
				if(l != i && l != j && book[k][l] == 1)flag = 0;//如果当前字符不是枚举到的字符并且当前字符串含有，那么这个字符串就不合法
				ans += flag * strlen(a[k]);//统计符合条件的字符串的总长度
			}
			Maxlen = max(Maxlen,ans);//更新答案取max
		}
	}
	cout << Maxlen;
	return 0;
}
```

这道题就$Over$了。

建议下调评分。（７分钟写完了的题目为什么是蓝题啊）

---

## 作者：zythonc (赞：0)

### 【分析过程】

首先可以很轻易的想到在扫描字符串时如果有两个以上不同的字符，那么这个字符串是没有用的

其次我们发现 ~~（数据范围小的可怜）~~ **合法的字符串只有两个不同的字符，我们可以用桶去实现dp**

开一个二维数组，第一维表示两个不同的字符中的第一个，第二维同第一维

如果只有一个不同的字符，那么第二维为0

因为字符的大小顺序有可能颠倒，所以我们正反存两次

这样，我们将 $26^2$ 个不同状态组合一一枚举，就可以求得最后的答案

```
#include<iostream>
using std::cin;
using std::cout;
std::string s;
int n,f[27][27],ans,a,b,cha,i,o;
bool c=0;
inline int max(int a,int b){
	return a>b?a:b;
}
int main(){
	std::ios::sync_with_stdio(0);
	cin>>n;
	for(i=1;i<=n;++i){
		a=0,b=0,c=0;
		cin>>s;
		for(o=0;o<s.length();++o){
			cha=s[o]-'a'+1;
			if((a^cha&&!b)||(a^cha&&b^cha)){
				if(!a) a=cha;
				else if(!b) b=cha;
				else{
					c=1;break;
				}
			}
		}
		if(!c){
			f[a][b]+=s.length();
			f[b][a]+=s.length();
		}
	}
	for(int i=1;i<=26;i++){
		for(int o=1;o<i;o++){
			f[i][o]+=f[i][0];
			f[i][o]+=f[o][0];
			ans=max(ans,f[i][o]);
		}
	}
	cout<<ans;
}
```

---

## 作者：Level_Down (赞：0)

### 题意简述

给定 $n$ 和 $n$ 个单词，从中选一些单词组合使得组合的单词只有2个及以下的不同字母，问这种组合单词的最大长度是什么？

### 方法

这道题有两个方法，一个是对每个字符串分析取或不取，另一个是枚举组合后单词拥有的那两个不同字符。

这里讲一下第二种方法（~~其实是因为不会第一种~~）。

基本思路就是首先在读入每个单词的时候将这个单词所包含的每种字母的个数和不同字母的个数都记录下来。

然后枚举 $a$ ~ $z$ 的字符两个。

对于任意一种情况，我们把每个字符串都扫过去，如果这个字符串所含不同字母个数小于等于2，并且所含的两个字母正好是枚举到的两个字母或者只有其中一个字母是枚举到的字母但是这个字符串所含的不同字母数为1。

如果符合条件，$sum$ 加等于此字符串的长度。

答案为 $ max(sum)$。

如果没听懂，就看代码理解吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,b[105][30],pd[105],sum,ans;
//b储存某字符串每种字母的个数，pd是某字符串不同字母的个数。
string s[105];
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)//在这里sum是某字符串不同字母的个数。
		{
			cin >> s[i];
			for (int j = 0; j < s[i].length(); j++)
				{
					if (b[i][s[i][j] - 'a' + 1] == 0) sum++;//如果之前没有统计到，sum++ 。
					b[i][s[i][j] - 'a' + 1]++;
				}
			pd[i] = sum;	
			sum = 0;
		}
	for (int i = 1; i <= 26; i++)
		{
			for (int j = i + 1; j <= 26; j++)//枚举 。
				{
					sum = 0;
					for (int k = 1; k <= n; k++)
						{
							if (((b[k][i] > 0 && b[k][j] > 0) || ((b[k][i] > 0 || b[k][j] > 0) && pd[k] == 1)) && pd[k] <= 2)
							//如上文的判断条件	。
								{
									sum += b[k][i] + b[k][j];
									//活用变量，这里的sum是当前枚举的情况的组合字符串最大长度 。
									//这里还可以写 sum += s[k].length();	
								}	
						}
					ans = max(ans,sum);		
				}	
		}
	cout << ans;		
	return 0;//AC!	
}
```


---

