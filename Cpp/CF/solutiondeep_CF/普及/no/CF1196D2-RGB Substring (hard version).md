# 题目信息

# RGB Substring (hard version)

## 题目描述

The only difference between easy and hard versions is the size of the input.

You are given a string $ s $ consisting of $ n $ characters, each character is 'R', 'G' or 'B'.

You are also given an integer $ k $ . Your task is to change the minimum number of characters in the initial string $ s $ so that after the changes there will be a string of length $ k $ that is a substring of $ s $ , and is also a substring of the infinite string "RGBRGBRGB ...".

A string $ a $ is a substring of string $ b $ if there exists a positive integer $ i $ such that $ a_1 = b_i $ , $ a_2 = b_{i + 1} $ , $ a_3 = b_{i + 2} $ , ..., $ a_{|a|} = b_{i + |a| - 1} $ . For example, strings "GBRG", "B", "BR" are substrings of the infinite string "RGBRGBRGB ..." while "GR", "RGR" and "GGG" are not.

You have to answer $ q $ independent queries.

## 说明/提示

In the first example, you can change the first character to 'R' and obtain the substring "RG", or change the second character to 'R' and obtain "BR", or change the third, fourth or fifth character to 'B' and obtain "GB".

In the second example, the substring is "BRG".

## 样例 #1

### 输入

```
3
5 2
BGGGG
5 3
RBRGR
5 5
BBBRR
```

### 输出

```
1
0
3
```

# AI分析结果

### 题目内容重写
# RGB 子串（困难版）

## 题目描述

简单版和困难版的唯一区别在于输入的大小。

给定一个由 $n$ 个字符组成的字符串 $s$，每个字符是 'R'、'G' 或 'B'。

还给定一个整数 $k$。你的任务是通过更改初始字符串 $s$ 中的最少字符数，使得更改后存在一个长度为 $k$ 的子串，该子串既是 $s$ 的子串，也是无限字符串 "RGBRGBRGB..." 的子串。

字符串 $a$ 是字符串 $b$ 的子串，如果存在一个正整数 $i$，使得 $a_1 = b_i$，$a_2 = b_{i + 1}$，$a_3 = b_{i + 2}$，...，$a_{|a|} = b_{i + |a| - 1}$。例如，字符串 "GBRG"、"B"、"BR" 是无限字符串 "RGBRGBRGB..." 的子串，而 "GR"、"RGR" 和 "GGG" 不是。

你需要回答 $q$ 个独立的查询。

## 说明/提示

在第一个例子中，你可以将第一个字符更改为 'R' 并获得子串 "RG"，或者将第二个字符更改为 'R' 并获得 "BR"，或者将第三、第四或第五个字符更改为 'B' 并获得 "GB"。

在第二个例子中，子串是 "BRG"。

## 样例 #1

### 输入

```
3
5 2
BGGGG
5 3
RBRGR
5 5
BBBRR
```

### 输出

```
1
0
3
```

### 算法分类
字符串、前缀和、枚举

### 题解分析与结论
题目要求通过最少的字符修改，使得字符串 $s$ 中存在一个长度为 $k$ 的子串，且该子串是无限字符串 "RGBRGBRGB..." 的子串。由于无限字符串 "RGBRGBRGB..." 只有三种可能的起始模式（RGB、GBR、BRG），因此我们可以分别枚举这三种模式，计算每种模式下需要修改的字符数，最终取最小值。

### 所选高分题解
#### 1. 作者：GeraldG (赞：7)
- **星级**: 5
- **关键亮点**: 使用前缀和优化计算，时间复杂度为 $O(n)$，代码简洁清晰。
- **核心思想**: 对于每种模式，计算前缀和数组，然后通过滑动窗口快速计算每个长度为 $k$ 的子串的修改次数。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int M=2e5+10;
char s[M];
int a[3][M];
int T,n,k,ans;
int main() {
    cin>>T;
    while(T--) {
        a[0][0]=a[1][0]=a[2][0]=0;
        cin>>n>>k;
        cin>>s;
        ans=M;
        string t="RGB";
        for(int i=0; i<n; i++) {
            for(int j=0;j<=2;j++){
                if(s[i]!=t[(i+j)%3])a[j][i+1]=a[j][i]+1;
                else a[j][i+1]=a[j][i];
            }
        }
        for(int i=0; i+k<=n; i++) {
            for(int j=0;j<=2;j++){
                ans=min(ans,a[j][i+k]-a[j][i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

#### 2. 作者：heyx0201 (赞：3)
- **星级**: 4
- **关键亮点**: 使用双指针优化，时间复杂度为 $O(n)$，代码实现简洁。
- **核心思想**: 对于每种模式，使用双指针维护一个长度为 $k$ 的窗口，通过滑动窗口计算修改次数。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const string kPos = "RGB";
int q,n,k;
string s;
void Solve(){
  cin >> n >> k >> s;
  int ans = n;
  for (int p = 0; p < 3; p++){
    int sum = 0;
    for (int i = 0; i < n; i++){
      sum += s[i] != kPos[(p + i) % 3];
      if (i + 1 >= k){
        ans = min(ans,sum);
        sum -= s[i - k + 1] != kPos[(p + i - k + 1) % 3];
      }
    }
  }
  cout << ans << '\n';
}
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin >> q;
  while (q--){
    Solve();
  }
  return 0;
}
```

#### 3. 作者：fjy666 (赞：3)
- **星级**: 4
- **关键亮点**: 使用滑动窗口优化，时间复杂度为 $O(n)$，代码实现清晰。
- **核心思想**: 对于每种模式，使用滑动窗口计算每个长度为 $k$ 的子串的修改次数。
```cpp
#include <algorithm>
#include <cstdio>
#define _for(i_,a_,b_) for(int i_ = a_;i_ < b_;++i_)
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int n,k,ans = 0x7fffffff;
char s[200050];
const char str[] = "RGB";
inline void getNxt(int& qwq){qwq = (qwq+1) % 3;}
void solve(int fjy){
	int cnt = 0;
	_rep(i,1,k){
		if(s[i] != str[fjy])++cnt;
		getNxt(fjy);
	}
	char *st = s+1,*ed = s+k;
	while(*ed != '\0'){
		ans = std::min(ans,cnt);
		if((*st) != str[((fjy-k)%3+3)%3])--cnt;
		++st;++ed;
		if(*ed != str[fjy])++cnt;
		getNxt(fjy);
	}
}
void solve(void){
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	ans = 0x7fffffff;
	solve(0);
	solve(1);
	solve(2);
	printf("%d\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
    return 0;
}
```

### 最优关键思路或技巧
1. **前缀和优化**: 通过前缀和数组快速计算任意子串的修改次数，时间复杂度为 $O(n)$。
2. **滑动窗口**: 使用滑动窗口维护一个长度为 $k$ 的子串，通过双指针快速计算修改次数，时间复杂度为 $O(n)$。
3. **模式枚举**: 由于无限字符串 "RGBRGBRGB..." 只有三种可能的起始模式，因此只需枚举这三种模式即可。

### 可拓展之处
1. **类似问题**: 可以扩展到其他循环模式的字符串匹配问题，如 "ABCABCABC..." 等。
2. **优化技巧**: 前缀和和滑动窗口是处理子串问题的常用技巧，可以应用到其他类似问题中。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
3. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)

---
处理用时：51.25秒