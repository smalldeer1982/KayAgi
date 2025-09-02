# Rudolf and the Ugly String

## 题目描述

Rudolf has a string $ s $ of length $ n $ . Rudolf considers the string $ s $ to be ugly if it contains the substring $ ^\dagger $ "pie" or the substring "map", otherwise the string $ s $ will be considered beautiful.

For example, "ppiee", "mmap", "dfpiefghmap" are ugly strings, while "mathp", "ppiiee" are beautiful strings.

Rudolf wants to shorten the string $ s $ by removing some characters to make it beautiful.

The main character doesn't like to strain, so he asks you to make the string beautiful by removing the minimum number of characters. He can remove characters from any positions in the string (not just from the beginning or end of the string).

 $ ^\dagger $ String $ a $ is a substring of $ b $ if there exists a consecutive segment of characters in string $ b $ equal to $ a $ .

## 说明/提示

In the first test case, for example, you can delete the $ 4 $ th and $ 9 $ th characters to make the string beautiful.

In the second test case, the string is already beautiful.

## 样例 #1

### 输入

```
6
9
mmapnapie
9
azabazapi
8
mappppie
18
mapmapmapmapmapmap
1
p
11
pppiepieeee```

### 输出

```
2
0
2
6
0
2```

# 题解

## 作者：kczw (赞：1)

# 题意
共 $t$ 组测试数据。

每组数据给定一由小写字母组成的长 $n$ 的字符串 $s$。

问最少须删除多少字符能使 $s$ 中无 `map` 和 `pie`。
# 思路
分析以下几种情况：

- 对于 `map` 来说，删掉任意一个字符都最优。
- 对于 `mmap` 来说，删掉 `a` 或者 `p` 最优。
- 对于 `mapp` 来说，删掉 `m` 或者 `a` 最优。
- 对于 `mmapp` 来说，删掉 `a` 最优。

所以，粗略地看来，对于 `map` 和 `pie` 的出现，删除中间字符最优，所以简单统计 `map` 和 `pie` 的总次数即可。

但是不难发现会有 `mapie` 这种专门钻牛角尖的数据，此时最优的方案却是删去 `p`。

看起来，情况变复杂了，但是不难发现，`mapie` 是唯一的特殊情况，所以只需要特判掉就可以了。

然后我直接用 find 函数做题，意外地 TLE 了。然后改为手写暴力匹配查找，循环枚举三个相邻的字符是否构成 `map` 和 `pie`，如果构成答案计数赠一并且将枚举的位置往后挪移三位，跳过后面即将枚举的两种情况。

之所以挪移三位，是因为未挪移前有 `map` 或者 `pie`，那么:

- 挪移一位则是 `ap` 加任意字母以及 `ie` 加任意字母，不可能匹配到 `map` 或 `pie`。
- 挪移两位有 `p` 加任意两个字母，和 `e` 加任意两个字母，匹配不到 `map`，若此时匹配到 `pie` 则属于上文提到的特殊情况 `mapie` 不予计数。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans;
string s;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cin>>s;
		ans=0;
		for(int i=0;i<n-2;i++){
			if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='p')ans++,i+=2;
			else if(s[i]=='p'&&s[i+1]=='i'&&s[i+2]=='e')ans++,i+=2;
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：CJKZS (赞：1)

这就是一个简单的字符串题

这里只要找到丑陋的单词"pie"和"map"

如果出现就删除最少数量字符数+1就可以了！

但这里要特判"mapie"的情况,如果按前面的方法会加两次

但这里只要把中间的"p"删掉就可以,

所以遇到这种情况特判只+1

AC代码：
```
#include<bits/stdc++.h> 
using namespace std;
int n,ans=0; 
int main(){
    cin>>n;
    int k;
    char s[1000010];
    for(int u=1;u<=n;u++){
        cin>>k;
        for(int i=1;i<=k;i++){
            cin>>s[i];
        }
        ans=0;
        int i=1;
        while(i<=k-2){//k-2 最后两位不会组成一个丑陋的子串 
            if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='p'&&s[i+3]=='i'&&s[i+4]=='e'){//mapie 的情况 
                ans++;
                i+=5;
            }else
            if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='p'){//map 的情况 
                ans++;
                i+=3;
            }else
            if(s[i]=='p'&&s[i+1]=='i'&&s[i+2]=='e'){//pie 的情况 
                ans++;
                i+=3;
            }else{
                i++;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

## CF1941C

### Sol

很明显，如果遇到字串 `map` 和 `pie` 删除其中一个即可。因为如果要有连续的字串 `map` 和 `pie`，子串中总会有一个单独的 `m` 或 `a` 或 `p` 或 `p` 或 `i` 或 `e`。因为如果每个字符都重复了至少一遍（如 `mmaappp` 或 `ppiiee`）就不会有字串 `map` 和 `pie`。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

using ll = long long;

const int kMaxN = 2e5 + 20, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

int n, ans = 0;
string s;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    cin >> n >> s, ans = 0;
    for (int i = 0; i < n; ) {
      if (s[i] == 'm' && s[i + 1] == 'a' && s[i + 2] == 'p') { // 如果遇到字串 "map"
        ++ ans; // 累加答案
        i += 3; // 直接跳到字串后面
      } else if (s[i] == 'p' && s[i + 1] == 'i' && s[i + 2] == 'e') { // 如果遇到字串 "pie"
        ++ ans; // 累加答案
        i += 3; // 直接跳到字串后面
      } else {
        ++ i; // 否则跳到下一个
      }
    }
    cout << ans << '\n'; // 输出答案
  } 
  return 0;
}
```

---

## 作者：Programming_Konjac (赞：0)

# 赛时思路
考虑贪心。

首先，我们为了截取字符串会多加上几个无用的字符，如：`jjjjj`，防止遍历的时候会超限。

我们分类讨论：

1. 截取 $3$ 位的字符串，如果是 `map`，那么删除 `a` 即可。

   证明：如果删除 `m`，那么如果前面有 `m`，那么会增加次数，反之，如果删除 `p`，那么如果后面有 `p`，那么会增加次数，所以删 `a` 是最合适的。
2. 截取 $3$ 位的字符串，如果是 `pie`，那么删除 `i` 即可。

   证明：如果删除 `p`，那么如果前面有 `p`，那么会增加次数，反之，如果删除 `e`，那么如果后面有 `e`，那么会增加次数，所以删 `i` 是最合适的。
   
3. 特殊情况：

   如果截取 $5$ 位的字符串为 `mapie`，如果按照上面的步骤的话，会进行 $2$ 次删除操作，但是，只要删除 `api` 中的任意一个字符，就构不成 `map` 和 `pie`，所以此类情况需要特判。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string c,s,p;
int t,n;
int main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		p=c;
		cin>>n>>s;
		s="j"+s;
		int len=s.size();
		s+="jjjjj";
		int cnt=0;
		for(int i=1;i<len; i++){
			string t=s.substr(i,5);
			if(t=="mapie"){
				cnt++;
				i+=4;
			}
			else if(t[0]=='m'&&t[1]=='a'&&t[2]=='p'){
				cnt++;
				i+=2;
			}
			else if(t[0]=='p'&&t[1]=='i'&&t[2]=='e'){
				cnt++;
				i+=2;
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
}
```

---

## 作者：yhylivedream (赞：0)

## 分析

发现如果出现了 `map` 或 `pie` 那么只需要删除一个即可。

但是发现对于 `mapie` 这种情况我们会多算一次，去掉一次即可。

## 代码

```cpp
# include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;
int T, n;
string s;

int main () {
  for (cin >> T; T; T --) {
    cin >> n >> s; s = ' ' + s;
    int cnt = 0;
    for (int i = 1; i + 2 <= n; i ++) {
      if (i + 4 <= n && s[i] == 'm' && s[i + 1] == 'a' && s[i + 2] == 'p' && s[i + 3] == 'i' && s[i + 4] == 'e') {
        cnt ++, i += 4;
      } else if (s[i] == 'm' && s[i + 1] == 'a' && s[i + 2] == 'p') {
        cnt ++, i += 2;
      } else if (s[i] == 'p' && s[i + 1] == 'i' && s[i + 2] == 'e') {
        cnt ++, i += 2;
      }
    }
    cout << cnt <<'\n';
  }
  return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

通过观察样例，我们可以发现：当出现子串 `map` 或 `pie` 时，我们只需要删掉中间的字符即可，否则会造成更多的损失。如 `mmmmmmmmmapppppppp`，如果一直删 `m` 和 `p`，就会耗费许多步数。而事实上，只需要删除一个 `a` 就行了。也就是说，如果出现了子串 `map` 或 `pie`，答案就加 $1$。 

但是，仅仅是统计 `map` 和 `pie` 出现的次数是不对的。比如这个样例：

`mapie`

观察到，`map` 尾部的 `p` 和 `pie` 头部的 `p` 连在了一起。刚才的程序会输出 $2$，因为有两个子串 `map` 和 `pie`。但事实上，只需要删掉一个公共的 `p` 就行了。

这种情况可以特判，但更好的做法是跳过当前子串，即在发现有子串为 `map` 或 `pie` 时，让 $i$ 加上 $3$，跳过这个长度为 $3$ 的子串。我们在编写代码的时候会写成让 $i$ 加上 $2$，因为在循环结束以后还会执行 $\text{i++}$。 

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int T, n;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T --) {
        cin >> n >> s;
        s = '#' + s;
        int ans = 0;
        for (int i = 1; i <= n - 2; i++) {
            string tmp = s.substr(i, 3);
            if (tmp == "map" || tmp == "pie") ans++, i += 2;
        }        
        cout << ans << "\n";
    }
    return 0;
} 
```

---

