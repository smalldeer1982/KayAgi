# Restoration of string

## 题目描述

A substring of some string is called the most frequent, if the number of its occurrences is not less than number of occurrences of any other substring.

You are given a set of strings. A string (not necessarily from this set) is called good if all elements of the set are the most frequent substrings of this string. Restore the non-empty good string with minimum length. If several such strings exist, restore lexicographically minimum string. If there are no good strings, print "NO" (without quotes).

A substring of a string is a contiguous subsequence of letters in the string. For example, "ab", "c", "abc" are substrings of string "abc", while "ac" is not a substring of that string.

The number of occurrences of a substring in a string is the number of starting positions in the string where the substring occurs. These occurrences could overlap.

String $ a $ is lexicographically smaller than string $ b $ , if $ a $ is a prefix of $ b $ , or $ a $ has a smaller letter at the first position where $ a $ and $ b $ differ.

## 说明/提示

One can show that in the first sample only two good strings with minimum length exist: "cfmailru" and "mailrucf". The first string is lexicographically minimum.

## 样例 #1

### 输入

```
4
mail
ai
lru
cf
```

### 输出

```
cfmailru
```

## 样例 #2

### 输入

```
3
kek
preceq
cheburek
```

### 输出

```
NO
```

# 题解

## 作者：yyandy (赞：4)

[题目链接](https://www.luogu.com.cn/problem/CF886D)  
这题看起来有点棘手，其实还是很好做的，并不需要什么高深的算法。  

首先很容易想到当给出的一个 most frequent 子串中有两个及以上的相同字符时是找不出符合条件的原串的。  
假设该情况下有符合条件的原串，那么原串中该重复字符出现次数肯定是比给出的这个 most frequent 子串多的，矛盾了。   
    
得出合法原串中每个不同字符最多出现一次也很容易。  
假设每个 most frequent 子串在原串中出现 $t$ 次。  
那么可以得出原串中每种出现了的不同字符都出现了 $t$ 次。   
当 $t=1$ 时，如果满足条件，那么肯定是最短。  
如果不满足条件，那么一定是有两个 most frequent 子串**相同的字符**不能**完全重合**。  
该种情况下，当 $t>1$ 时，两个 most frequent 子串相同的字符仍然不能完全重合，即仍然不能满足条件，没有合法原串。  
所以如果有原串，每个不同字符最多出现一次。    

我们可以把给出的字符串看成一个个条件。  
例如这个字符串 abc，
我们可以得出在原串中，  
字符 a 在 b 前一个，  
字符 b 在 a 后一个，字符 b 在 c 前一个，  
字符 c 在 b 后一个。  
显然，当给出条件矛盾时要输出 NO。  
然后，根据这些条件我们就可以生成出原串了。  
需要注意的是，这样得到的原串可能有好几块，最后需要进行排序才行。  
还有，给出的条件可能会构成环，需要判断，如果有环，那么就输出 NO。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[2][10000];
//x[0][i],表示ASCLL码为i的字符前面的字符
//x[1][i],表示ASCLL吗为i的字符后面的字符
string st[120001],s[120001];
int tt[12001],t[1201],v[12001];
int n,i,j,k[120001],ii,kk;
int main(){
	cin>>n;
	for(i=1;i<=n;++i){
		cin>>st[i];
		k[i]=st[i].length();
		for(j=0;j<k[i];++j){
		tt[st[i][j]]=1;//tt表示一个字符是否出现过
		if(t[st[i][j]])//t表示一个字符是否在这个串中出现过
        {
        cout<<"NO";return 0;
        /*如果原串中有相同的字符*/
        }
		t[st[i][j]]=1;
	}
			for(j=0;j<k[i];++j)t[st[i][j]]=0;
	}
	for(i=1;i<=n;++i){
		for(j=0;j<k[i];++j){
			if(j!=0){
				if(x[0][st[i][j]]>0&&x[0][st[i][j]]!=st[i][j-1]){
                //条件矛盾
					cout<<"NO";return 0;
				}
				x[0][st[i][j]]=st[i][j-1];
			}
			if(j!=k[i]-1){
				if(x[1][st[i][j]]>0&&x[1][st[i][j]]!=st[i][j+1]){
                //条件矛盾
				cout<<"NO";return 0;
				}
				x[1][st[i][j]]=st[i][j+1];
			}
		}
	}
	for(i=0;i<=200;++i){
	if(tt[i]&&x[0][i]==0){
    //如果ASCLL码为i的字符出现过且他前面没有任何字符
    //那么说明这个字符是一个新的"块"的开始
		ii=i;++kk;v[ii]=1;
		while(ii){	
		s[kk]+=char(ii);
		v[ii]=1;
		ii=x[1][ii];
		}
        
	}
}
for(i=0;i<=200;++i)
if(tt[i]&&!v[i]){
	cout<<"NO";
    //如果出现过得字符没有被加入到原串中
    //那么此时一定是出现了环
	return 0;
}
	sort(s+1,s+kk+1);//排序，取字典序最小
	for(i=1;i<=kk;++i)
	cout<<s[i];
}
```
太菜了，可能会有错误。  
所以大家有什么问题尽管提出。

---

## 作者：Wander_E (赞：0)

对于每一个字符串 $s$，从 $s_i$ 连一条**有向边**到 $s_{i+1}$。

#### 无解情况：

1.  由于原串与字串字母的前后顺序一致且唯一，所以不允许出现字符 $c$ 同时向 $c'$ 和 $c''$ 连边。

1.  如果字符串 $s$ 在 字符串 $S$ 中出现了 $x$ 次，则 $s$ 的每个子串 $s'$ 也在 $S$ 中出现了 $x$ 次。若存在 $s$ 的子串 $s''$ 使得 $s' = s''$ 且 $s'$ 与 $s''$ 不重合，则 $s'$($s''$) 至少在 $S$ 中出现 $2x$ 次，与题意矛盾。因此 $s$ 中不存在重复字符，即图中没有自环。

1. 如果图中存在环，即存在字符串 $a$、$b$ 使得 $a_1 = b_1$，$a_{len_a} = b_{len_b}$，于是出现了两组相同字符，与第二点矛盾。因此图中无环，这点可以用拓扑解决。


如果有解则按照字典序遍历每一条由字符串组成的链首（有解的情况一定是链），DFS 求解即可。

#### AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int edge[30][30];
int in[30], t[30];
bool exist[30];
string s;
bool vis[30];
string ans;

void tupo()
{
    queue<int> q;
    int cnt = 0;
    for (int i = 0; i < 26; i++)
        if (!in[i] && exist[i])
            q.push(i);
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        cnt++;
        for (int i = 0; i < 26; i++)
        {
            if (!edge[t][i] || vis[i])
                continue;
            vis[i] = 1;
            in[i]--;
            if (in[i] <= 0)
                q.push(i);
        }
    }
}

void dfs(int u)
{
    int cnt = 0;
    ans += char(u + 'a');
    for (int i = 0; i < 26; i++)
    {
        if (!edge[u][i])
            continue;
        if (vis[i])
        {
            cout << "NO\n";
            exit(0);
        }
        cnt++;
        vis[i] = 1;
        dfs(i);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        exist[s[0] - 'a'] = 1;
        for (int j = 1; j < s.size(); j++)
        {
            exist[s[j] - 'a'] = 1;
            edge[s[j - 1] - 'a'][s[j] - 'a'] = 1;
            in[s[j] - 'a']++;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (edge[i][i])
        {
            cout << "NO\n";
            return 0;
        }
    }
    memcpy(t, in, sizeof(in));
    tupo();
    memcpy(in, t, sizeof(in));
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < 26; i++)
    {
        if (exist[i] && !vis[i] && !in[i])
            dfs(i);
    }
    for (int i = 0; i < 26; i++)
    {
        if (in[i] && !vis[i])
        {
            cout << "NO\n";
            exit(0);
        }
        int cnt = 0;
        for (int j = 0; j < 26; j++)
        {
            if(cnt > 1)
            {
                cout << "NO\n";
                exit(0);
            }
            cnt += edge[i][j];
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

