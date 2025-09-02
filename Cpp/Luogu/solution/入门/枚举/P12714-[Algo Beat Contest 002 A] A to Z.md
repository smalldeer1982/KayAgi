# [Algo Beat Contest 002 A] A to Z

## 题目背景

| Problem | Score | Idea | Std | Data | Check | Solution |
| :----------------------------------: | :---: | :---------------------------------------------------: | :---------------------------------------------------: | :---------------------------------------------: | :-------------------------------------------------: | :----------------------------------------------------------: |
| $\text{A - A to Z}$ | $100$ |  [LostKeyToReach](https://www.luogu.com.cn/user/764666)    |  [LostKeyToReach](https://www.luogu.com.cn/user/764666)    | [LostKeyToReach](https://www.luogu.com.cn/user/764666)     |    [zhoumurui](https://www.luogu.com.cn/user/305928)      |  [Link](https://www.luogu.com.cn/article/1gh0j55t) by  [zhoumurui](https://www.luogu.com.cn/user/305928)   |


71 for ever

## 题目描述

你有 $n$ 个字符串，请求出满足字符串里**所有字符互不相同**的字符串数量。

**字符串中只含有小写字母。**

## 说明/提示

**【数据范围】**

- $1 \le n \le 100$。
- 每个字符串的长度不超过 $100$。 

## 样例 #1

### 输入

```
3
takahashi
aoki
snuke```

### 输出

```
2```

# 题解

## 作者：bcdmwSjy (赞：8)

~~差点抢到首杀 /fn。~~

给你 $n$ 个字符串，求出字符串里所有字符互不相同的字符串数量。

这显然可以用 Python 中的 `set` 函数计算，这个函数可以给一个可迭代对象（如字符串、列表等）转换成集合（自动去重），然后判断集合的长度和原字符串是长度是否相等就好了。

```python
n=int(input())
cnt=0
for i in range(n):
    s=input()
    if len(set(s))==len(s):cnt+=1
print(cnt)
```

~~但由于我最开始一直在思考怎么写最快导致比第一慢了 10s 才过。~~

---

## 作者：weifengzhaomi (赞：7)

作为一道水题，自然不用太难的做法。

## 思路

先写一个函数，每次传进一个字符串，用暴力枚举两个字符来判断两个是否有相同的字符，如果有，`return false;`。否则，`return true;`

然后，暴力枚举每个字符串，传进函数里，如果`return true;`，则答案加一。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[30],l,ans;
char s[110][110];
inline bool clec(int x){
	l = strlen(s[x] + 1);
	for (int i = 1;i <= l;i++)
		for (int j = 1;j <= l;j++){
			if (i == j) continue;
			if (s[x][i] == s[x][j]) return false;
		}
	return true;
}
int main(){
	scanf("%d",&n);
	for (int i = 1;i <= n;i++) scanf("%s",s[i] + 1);
	for (int i = 1;i <= n;i++) ans += clec(i);
	printf("%d\n",ans);
}
```

---

## 作者：zhoumurui (赞：6)

### 题面展示

给出 $n$ 个字符串，询问其中有几个是所有字符各不相同的。

### 解题思路

这里给出 `set` 做法。

`set<T>` 是一种 STL 数据结构，用来维护由 `T` 组成的集合。下面假设一个集合的名字为 `s`，一个 `T` 类型的变量为 `t`。

- `s.insert(t);` 将 `t` 插入集合中。
- `s.find(t)` 寻找 `t` 是否在集合 `s` 中，如果存在，以 `set<T>::iterator` 的形式返回 `t` 在 `s` 中的位置；如果不存在，返回 `s.end()`。

那么容易用 `set` 判断一个字符串的所有字符是否各不相同。

### 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
    int n;
    cin>>n;
    int cnt=0;
    for (int i=1;i<=n;i++){
        string s;
        cin>>s;
        set<char> p;
        int flag=1;
        for (int j=0;j<s.length();j++){
            if (p.find(s[j])!=p.end()){
                flag=0;
                break;
            }
            p.insert(s[j]);
        }
        cnt+=flag;
    }
    cout<<cnt<<"\n";
    return 0;
}
```

---

## 作者：LoongPig (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P12714)

## 思路

对于每一个字符串，进行下标计数。

如果有一个字符出现次数大于 $1$，那这个字符串就不满足所有字符互不相同。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,cnt[255],ans;
int main(){
    cin>>n;
    while(n--){
        memset(cnt,0,sizeof cnt);//记得清空
        string s;
        cin>>s;
        for(int i=0;i<s.size();i++) cnt[s[i]]++;
        bool flag=false;
        for(int i=0;i<s.size();i++)
            if(cnt[s[i]]>1) flag=true;
        if(!flag)ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：zhouxiaodong (赞：4)

# 思路
依次循环字符串的每一个字符
- 如果已经有过了，就不符合题意“**字符串里字符互不相同**”。
- 否则，累加答案。

模拟一遍，最后输出累加结果即可。
# AC Code
```````````````cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int cnt=0;
    for(int i=1;i<=n;i++)
	{
        string str;
        cin>>str;
        bool ch[26]={false};
        bool flag=true;//默认所有字母都没出现过
        for(char c:str)//循环每一个字符
		{
            if(ch[c-'a'])//如果这个字符出现过
			{
                flag=false;
                break;//跳出循环
            }
            ch[c-'a']=true;
        }
        if(flag)//没出现过，累加
		{
            cnt++;
        }
    }
    cout<<cnt;
    return 0;
}
```````````````

---

## 作者：Clare613 (赞：3)

## 思路：
水题，因为**字符串中只含有小写字母**，所以长度大于 $26$ 的直接淘汰。然后给字符串的每一按字典序排序，如果有相邻两个字符相等的就淘汰，即一个字符出现了多次。最后统计未被淘汰的字符串的数量即可。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	cin.tie(0)->sync_with_stdio(0);
	int T,ans=0;
	cin>>T;
	while(T--){
		string x;
		cin>>x;
		if(x.size()>26){
			continue;
		}
		bool flag=0;
		sort(x.begin(),x.end());
		for(int i=1;i<x.size();i++){
			if(x[i]==x[i-1]){
				flag=1;
				break;
			}
		}
		if(flag==0) ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：chenzefan (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P12714)
## 前言
没打比赛，前来水题解。
## 思路
字符串判断题。

题意：给定 $n$ 个字符串，求其中满足串内无重复字符的字符串的数量。

开一个 map 用来统计字符串中的字符是否出现，注意，因为题目多测，所以每次都要清空。

因为判断字符，所以 map 可以这样开：`map <char,int> mp`。

清空可以用 clear 函数，像这样：`mp.clear()`。

此题很简单，直接上代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,cnt=0;map <char,int> mp;
	scanf("%d",&n);
	while(n--){
		mp.clear();//多测需清空 
		string s;
		cin>>s;
		bool f=0;//进行标记 
		for(int i=0;i<s.size();i++){
			if(mp[s[i]]!=0){f=1;break;}
			mp[s[i]]=1;//标记 
		}
		if(f==0) cnt++;//统计答案 
	} printf("%d",cnt);
	return 0;
}
```
撒花。

---

## 作者：niuniudundun (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P12714)

# Problem

$n$ 个字符串，求出满足字符串里两个字符互不相同的字符串数量。

# Solution

~~赛时没读懂题~~。

题面也就是说有 $n$ 个字符串 $s$，要求出满足对于 $s$ 的所有下标 $j,k$，满足 $s_j\not = s_k$ 的数量。可以定义一个桶 $t$，判断是否 $t_{s_i}$ 已经被标记，被标记说明 $s$ 不满足，否则 $s$ 满足条件。对每个字符串判断。

# Code

复杂度：$O(nl)$，$l$ 是 $s$ 长度。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[101];
int n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		bool b=1;
		int t[26];
		memset(t,0,sizeof(t));
		int l=s[i].length();
		for(int j=0;j<l;j++){
			if(t[s[i][j]-'a']==1){
				b=0;
				break;
			}
			t[s[i][j]-'a']=1;
		}
		if(b==1) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：GeorgeDeng (赞：2)

字符串处理题。

## Solution

对于每个字符串 $s$，遍历每两个不一样的位置，如果这两个位置相等，那么这个字符串不符合要求。如果遍历到头都没有不符合要求过，那么就是符合要求的，答案加一。

思路就这么点，代码很简单。

## code

```cpp
#include <iostream>
using namespace std;

string s[105];//因为我是蒟蒻所以我只会这样存字符串
int n;
int ans;//记录答案
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i = 1;i<=n;i++){
        cin>>s[i];
    }
    for(int i = 1;i<=n;i++){
        bool flag = true;//标记是否合法
        for(int j = 0;j<s[i].length();j++){
            for(int k = j+1;k<s[i].length();k++){//枚举两个位置
                if(s[i][j]==s[i][k]){
                    flag = false;
                    break;//如果不满足条件，直接break
                }
            }
            if(!flag) break;//小优化
        }
        ans+=flag;//加上答案
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Dlwlrma_ZZX (赞：2)

《最简单的题往往采用最朴素的解题方法》
## 题意

  给定若干个字符串 $s$，求这些字符串中不出现重复字符的串的个数。
  
## 思路

  分别判断每个串的情况然后加和。
  首先可以特判，若 $|s|>26$，则该串肯定会出现重复字符。
  除开特判过的串可以使用桶排统计判定。若该字符出现过就重复了，未出现过就将该字符标记为访问过。若最后该串跑完了则说明该串符合条件，可以加和。
  
## 注意

  要及时清空标记数组，防止不同串的判断相互影响。
  
## 代码
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
int n,cnt;
string s;
bool exist[27];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s.size()>26) continue;
		memset(exist,0,sizeof(exist)) ;
		int j;
		for(j=0;j<s.size();j++)
		  if(exist[s[j]-'a']) break;
		  else exist[s[j]-'a']=1;
		if(j==s.size()) cnt++;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：New_Void (赞：2)

## [P12714 [Algo Beat Contest 002 A] A to Z](https://www.luogu.com.cn/problem/P12714)

### 思路

我们可以想到，这道题其实可以写成把字符串去重，之后看去重后的字符串和原字符串的长度是否相等，相等就将答案加一，最后输出答案，而去重可以用 ```set``` 来做。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int cnt=0;
    while (n--){
        string s;
        cin>>s;
        set<char> s1;
        for (int i=0;i<s.size();i++){
            s1.insert(s[i]);
        }
        if (s1.size()==s.size()){
            cnt++;
        }
    }
    cout<<cnt;
    return 0;
}

```

---

## 作者：封禁用户 (赞：1)

# P12714 题解

## 思路

暴力循环每个字符串（因为长度只有 $100$），查看其中的每个字符是否出现过。可以使用一个标记数组来记录已经出现过的字符。然后枚举一遍，如果某个字符已经被标记过，则说明该字符串不满足条件；否则，标记该字符，最后输出答案。

## [AC](https://www.luogu.com.cn/record/219725746) 代码
```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,sum = 0;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int jj[26] = {0};
        int bj = 1;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            int x = c - 'a';
            if (jj[x]) {
                bj = 0;
                break;
            }
            jj[x] = 1;
        }
        if (bj) sum++; 
    }
    cout << sum;
    return 0;
}
```
~~为了方便查看，我用 Deepseek 优化了一下格式。~~

---

## 作者：Vct14 (赞：1)

对于一个字符串，我们可以直接枚举判断 $i,j$ 位置的字母是否是相同的。时间复杂度 $O(n|s|^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n;cin>>n;int ans=0;
    while(n--){
        string s;cin>>s;int l=s.size();bool ok=1;
        for(int i=0; i<l; i++) for(int j=0; j<i; j++) if(s[i]==s[j]){ok=0;break;}
        if(ok) ans++;
    }
    cout<<ans;
    return 0;
}
```

当然我们也可以用一个数组（或者 `map`）存储每个字母是否出现过。时间复杂度 $O(n|s|)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[30];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n;cin>>n;int ans=0;
    while(n--){
        for(int i=0; i<26; i++) a[i]=0;
        string s;cin>>s;int l=s.size();bool ok=1;
        for(int i=0; i<l; i++){
            if(a[s[i]-'a']){ok=0;break;}
            a[s[i]-'a']=1;
        } 
        if(ok) ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：M1__ (赞：0)

# 题解：P12714 [Algo Beat Contest 002 A] A to Z

[Link](https://www.luogu.com.cn/problem/P12714)

- 思路：将字符数组转换成每项在 $1 \sim 26$ 之间的数组。

- 接下来用桶来查重即可，注意多测清空。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3+10;
ll T,num[N],t[N],ans=0,temp;
string s;
int main(){
	cin>>T;
	temp=T;
	while(T--){
		cin>>s;
		ll cnt=0; //多测清空
		for(int i=0;i<s.size();i++) num[cnt++]=s[i]-'a'+1; //运用 ASCII 码表进行转换
		for(int i=0;i<27;i++) t[i]=0; //数组手动清空
		bool f=0;
		for(int i=0;i<cnt;i++){
			t[num[i]]++; //运用桶进行计数。实际上桶开到 27 就可以 
			if(t[num[i]]>1) f=1;
		}
		if(f) ans++;
	}	
	cout<<temp-ans;
    return 0；
}


```

---

## 作者：uncle_steve (赞：0)

**算法：模拟即可**

## 解题思路：

**所有字符互不相同**的字符串数量用 `ans` 保存。

对于每一次询问：

- 使用一个桶记录这个字符是否出现过（直接用 ASCII 码存即可），0 代表没出现过，1 代表出现过了
- 对于每个字符，如果对应桶中为 1，则这个字符串不是**所有字符互不相同**的字符串，直接退出并 `ans--` 即可。
- 每处理完一个字符串，就 `ans++`。

### 注意事项：

每个字符串处理完后桶要清空。

## 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a[300],ans=0;//桶数组
    string s;
    cin>>n;
    while(n--){
        cin>>s;
        for(int i=0;i<s.size();i++){
            if(a[s[i]]==1){
                ans--;
                break;//重复则退出
            } 
            a[s[i]]=1;//标记桶
        }
        ans++;
        memset(a,0,sizeof(a));//清空桶
    }
    cout<<ans<<endl;

    return 0;
}
```

---

## 作者：littlesnake (赞：0)

- 思路

直接遍历字符串，用哈希判断这个字符是否出现过，就这样来 $n$ 次，每次定义一个是否互不相同的变量记录即可。这样就可以用哈希记录第 $i$ 个字符串的这个字符是否出现过即可。注意初始化！

当然哈希不能搞，我们使用 `map` 即可，这是 STL 库中的一个东西，可以把一个参数映射为另一个参数，适合解决此问题。

- 代码

```cpp
# include <bits/stdc++.h>

using namespace std;

int n, ans;
string s;

int main () {

	ios::sync_with_stdio (0);
	cin.tie (0), cout.tie (0);
	cin >> n;
	while (n --) {
		cin >> s;
		map <char, int> mp;
		bool flag = 1;
		for (char c : s) {
			if (mp[c]) flag = 0;
			mp[c] = 1;
		}
		if (flag) ans ++;
	}
	cout << ans;

	return 0;
}

```

---

## 作者：jinfanhao (赞：0)

我们这里给出用映射表解决问题的方法。\
首先，先把里面的字母插到里面，如果字母存在过了，那么这个就不满足所有字符互不相同的条件，如果所有的都插了进去，发现没有重复，那么就满足条件。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=101;
int n,sum;
string op;
map<char,bool> mp; 
signed main(){
	scanf("%lld",&n);
	sum=n;
	for(int k=1; k<=n; ++k){
		cin >> op;
		mp. clear();
		for(int i=0; i<op.size(); ++i){
			if(mp[op[i]]){
				--sum;
				break;
			}
			mp[op[i]]=true;
		}
	}
	printf("%lld",sum);
	return 0;
}
```

---

