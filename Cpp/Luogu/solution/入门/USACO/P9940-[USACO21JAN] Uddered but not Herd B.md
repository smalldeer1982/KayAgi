# [USACO21JAN] Uddered but not Herd B

## 题目描述

一个鲜为人知的事实是，奶牛拥有自己的文字：「牛文」。牛文由 $26$ 个字母 `a` 到 `z` 组成，但是当奶牛说牛文时，可能与我们所熟悉的 `abcdefghijklmnopqrstuvwxyz` 不同，她会按某种特定的顺序排列字母。

为了打发时间，奶牛 Bessie 在反复哼唱牛文字母歌，而 Farmer John 好奇她唱了多少遍。

给定一个小写字母组成的字符串，为 Farmer John 听到 Bessie 唱的字母，计算 Bessie 至少唱了几遍完整的牛文字母歌，使得 Farmer John 能够听到给定的字符串。Farmer John 并不始终注意 Bessie 所唱的内容，所以他可能会漏听 Bessie 唱过的一些字母。给定的字符串仅包含他记得他所听到的字母。 

## 说明/提示

### 样例解释 1

在这个样例中，牛文字母表与日常的字母表的排列一致。

Bessie 至少唱了三遍牛文字母歌。有可能 Bessie 只唱了三遍牛文字母歌，而 Farmer John 听到了以下被标记为大写的字母。

`abcdefghijklMnOpqrstuvwxyz`  
`abcdefghijklmnOpqrstuvwxyz`  
`abcDefghijklmnopqrstuvwxyz`  

### 测试点性质

- 测试点 $2-5$ 中，牛文字母表与日常的字母表相同。
- 测试点 $6-10$ 没有额外限制。

## 样例 #1

### 输入

```
abcdefghijklmnopqrstuvwxyz
mood```

### 输出

```
3```

# 题解

## 作者：xu222ux (赞：4)

# [P9940](https://www.luogu.com.cn/problem/P9940)

## 贪心思路

看看听到字母的顺序，如果第 $i$ 个字母的出现位置比第 $i-1$ 个字母出现位置靠前，那么一定又多唱了一首歌。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int tmp[30];
int ans=1,q;
int main(){
	cin>>t>>s;
	for(int i=0;i<26;i++)tmp[t[i]-'a']=i;
	for(int i=0;i<s.length();i++){
		if(i==0)continue;
		if(tmp[s[i]-'a']<=tmp[s[i-1]-'a'])ans++;//康康是否多唱了一首歌
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：huangzhixia (赞：3)

**[题目传送门](https://www.luogu.com.cn/problem/P9940)**

### 题意

牛文是包含 $26$ 个字母，但顺序可能不一样。

现在给出一个字符串，也就是牛文字母表顺序。再给出一个字符串，表示 Farmer John 他记得他所听到的字母。

现在我们要求 Bessie 最少唱了多少遍完整的牛文字母歌。

### 思路

这是到贪心题。

遍历一下听到的字母的顺序，看看第 $i$ 个字母出现的位置是不是比第 $i - 1$ 个字母出现的位置靠前，如果是靠前，就肯定多唱了一首完整的歌。否则，就没有。

详见代码。

### code:

```c
#include <bits/stdc++.h> //万能头文件。 

using namespace std; //命名空间。 

string s1, s2; //这边字符串的话用 string。 

int answer = 1, a[26], pos;

int main(){
    cin >> s1 >> s2; //读入 string，因为时间复杂度支持就不用 scanf 了。 
    for (int i = 0; i < 26; i++) {
		int x = s1[i] - 'a';    // 预处理字符串。 
		a[x] = i;
	}
	int l = s2.size(); // 取一下 s2 的长度。 
    for (int i = 0; i < l; i++){ // 这里的 l 再上面取过长度了，之所以不在这里写 size 是因为很慢。 
        if (!i)        // i 等于零的话不用看了，绝对不会唱完一首个。 
			continue;
        if (a[s2[i] - 'a'] <= a[s2[i - 1] - 'a']) //思路里讲的贪心，看看他是不是比前一个靠前，是的话把答案加一。 
			answer += 1;
    }
    printf("%d\n", answer); //输出。 
}
```


---

## 作者：_fallen_leaves_ (赞：2)

## 思路
拿一个指针来指第二个字符串，跟第一个字符串来做比较，如果一样指针往后挪一位，否则就一直遍历第一个字符串，直到指针指向最后一个数位置。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h=0,sum=0;
    string s,x;
    cin>>s>>x;
    while(1)
    {
    	sum++;
    	for(int i=0;i<s.size();i++)
    		if(x[h]==s[i]) h++;
    	if(h==x.size()) break;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：语录 (赞：2)

### 考点：字符串基础。
### 简要思路：
- 首先将字母表按照输入次序重新编号。

```cpp
int num[27]; //字符x的编号
char a[27]; //输入的字母表

...

for(int i=0;i<=25;i++) num[a[i]-'a'+1]=i+1;
```

- 接下来将其听到的字母歌转换为编号，当当前编号 $\le$ 上一个的编号时，就说明唱完了一首歌。

```cpp
char b[1001];

...

int sum=strlen(b);
int last=0;
int ans=1;//至少唱了一首歌
for(int i=0;i<sum;i++){
    if(num[b[i]-'a'+1]<=last) ans++;
    last=num[b[i]-'a'+1];
}
```

- 累加求和即可得出最终答案。
### 最终代码：

```cpp
#include<bits/stdc++.h>
#define ll long long 
char a[27],b[1001];
ll num[27],ans=1; 
using namespace std;
int main(){
    cin >>a;
    cin >>b;
    for(int i=0;i<=25;i++) num[a[i]-'a'+1]=i+1;
    ll sum=strlen(b);
    ll last=0;
    for(int i=0;i<sum;i++){
        if(num[b[i]-'a'+1]<=last) ans++;
        last=num[b[i]-'a'+1];
    }
    cout <<ans;
    return 0;
}
```


---

## 作者：FreedomKing (赞：1)

### 题目大意/简化题意

个人认为翻译给的题意不大明确。

给出两个字符串 $s,t$，其中 $s$ 为 $a,b,c,\dots,z$ 的排列，表示在“牛文”中字母的顺序；$t$ 为由任意个出现任意次数的小写字母组成的字符串，需要你求出 $t$ 中有多少个 $S(t_{i+1})\le S(t_i)$，$S(x)$ 表示 $x$ 在 $s$ 中的顺序。

### 思路

利用 `map` 或数组之类的直接模拟这个过程即可。

剩下的见注释。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=1e4+5;
const int mod=1e9+7;
int a[N],b[N],f[mN][mN],n,m,k,ans;
string s,t;
map<int,int>mp;
signed main(){
	cin>>s>>t;
	for(int i=0;i<26;i++) mp[s[i]]=i;//记录顺序
	int len=t.size();
	for(int i=0;i<len;i++) if(mp[t[i+1]]<=mp[t[i]]) ans++;//统计
	cout<<ans;
	return 0;
}
```

---

## 作者：tder (赞：1)

模拟即可。

---

令字母表为 $a$，听到唱的字母为 $b$。

用指针 $k$ 记录当前下一个等待被听到的字符为 $b$ 的第 $k$ 位，枚举 $a$ 的每一位，若该位等于 $b$ 的第 $k$ 位，$k\leftarrow k+1$ 即可。当听完了所有的 $b$ 中的字母，程序结束。

时间复杂度 $O(|a|\cdot|b|)$，其中 $|s|$ 表示 $s$ 的长度。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
string a, b;
int k, cnt;
signed main() {
	cin>>a>>b;
	while(++cnt) {
		for(int i = 0; i < a.length(); i++)
			if(a[i] == b[k]) {
				k++;
				if(k == b.length()) {
					cout<<cnt<<endl;
					return 0;
				}
			}
	}
	return 0;
}
```

---

## 作者：FurippuWRY (赞：1)

设两字符串分别为 $a,b$。

可以从 $a_0$ 开始，遍历 $b$，如果 $a_i=b_j$，$i$ 加一，然后继续遍历 $b$，重复上述操作。如果 $a$ 还没有遍历完，那么从 $b_0$ 开始再遍历一次，继续搜相同字符。每遍历一次，次数 $ans$ 就加一，最后输出 $ans$ 即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

string a, b;
int i = 0, ans = 0;

int main() {
    
    cin >> a >> b;
    while (i <= b.size()) {
        for (int j = 0; j <= a.size(); ++j) {
            if (a[j] == b[i]) i++;
        }
        ++ans;
    }
    cout << ans;
    
    return 0;
    
}
```

---

## 作者：s11255 (赞：0)

# P9940 [USACO21JAN] Uddered but not Herd B

### [题目传送门](https://www.luogu.com.cn/problem/P9940)

~~本蒟蒻的第一篇题解，大佬勿喷。~~
***

## 思路


首先我们发现，求的是所唱的**完整**的牛文字母歌的**最小次数**，题目数据又不大，瞬间就能想到**模拟**，模拟唱歌过程即可。

话不多说，上代码！（C++）
```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
	string a,b;
	int cnt=0,sum=0;
	cin>>a>>b;
	while(cnt<b.size()){//如果Farmer John听到的字母都出现了，结束循环。
		sum++;//又唱了一遍。
		for(int i=0;i<a.size();i++){//遍历牛文字母表，判断是否出现。
			if(a[i]==b[cnt]){
				cnt++;//听到一个字母。
			}
		}
	}
	cout<<sum;
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/139957488)

---

