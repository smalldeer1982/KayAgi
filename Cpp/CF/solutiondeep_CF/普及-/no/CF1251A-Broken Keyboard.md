# 题目信息

# Broken Keyboard

## 题目描述

Recently Polycarp noticed that some of the buttons of his keyboard are malfunctioning. For simplicity, we assume that Polycarp's keyboard contains $ 26 $ buttons (one for each letter of the Latin alphabet). Each button is either working fine or malfunctioning.

To check which buttons need replacement, Polycarp pressed some buttons in sequence, and a string $ s $ appeared on the screen. When Polycarp presses a button with character $ c $ , one of the following events happened:

- if the button was working correctly, a character $ c $ appeared at the end of the string Polycarp was typing;
- if the button was malfunctioning, two characters $ c $ appeared at the end of the string.

For example, suppose the buttons corresponding to characters a and c are working correctly, and the button corresponding to b is malfunctioning. If Polycarp presses the buttons in the order a, b, a, c, a, b, a, then the string he is typing changes as follows: a $ \rightarrow $ abb $ \rightarrow $ abba $ \rightarrow $ abbac $ \rightarrow $ abbaca $ \rightarrow $ abbacabb $ \rightarrow $ abbacabba.

You are given a string $ s $ which appeared on the screen after Polycarp pressed some buttons. Help Polycarp to determine which buttons are working correctly for sure (that is, this string could not appear on the screen if any of these buttons was malfunctioning).

You may assume that the buttons don't start malfunctioning when Polycarp types the string: each button either works correctly throughout the whole process, or malfunctions throughout the whole process.

## 样例 #1

### 输入

```
4
a
zzaaz
ccff
cbddbb
```

### 输出

```
a
z

bc
```

# AI分析结果

### 题目内容
# 坏掉的键盘

## 题目描述
最近，Polycarp 注意到他键盘上的一些按键出现了故障。为了简化问题，我们假设 Polycarp 的键盘包含26个按键（每个按键对应拉丁字母表中的一个字母）。每个按键要么工作正常，要么出现故障。

为了检查哪些按键需要更换，Polycarp 按顺序按下了一些按键，屏幕上出现了一个字符串 $s$。当 Polycarp 按下一个字符为 $c$ 的按键时，会发生以下两种情况之一：
- 如果该按键工作正常，字符 $c$ 会出现在 Polycarp 正在输入的字符串末尾；
- 如果该按键出现故障，字符 $c$ 会连续出现两次，即两个 $c$ 出现在 Polycarp 正在输入的字符串末尾。

例如，假设对应字母 a 和 c 的按键工作正常，而对应字母 b 的按键出现故障。如果 Polycarp 按顺序按下按键 a、b、a、c、a、b、a，那么他正在输入的字符串变化如下：a $\rightarrow$ abb $\rightarrow$ abba $\rightarrow$ abbac $\rightarrow$ abbaca $\rightarrow$ abbacabb $\rightarrow$ abbacabba。

给定一个在 Polycarp 按下一些按键后出现在屏幕上的字符串 $s$。请帮助 Polycarp 确定哪些按键肯定是正常工作的（也就是说，如果这些按键中有任何一个出现故障，这个字符串就不可能出现在屏幕上）。

你可以假设在 Polycarp 输入字符串的过程中，按键不会突然出现故障：每个按键要么在整个过程中都正常工作，要么在整个过程中都出现故障。

## 样例 #1
### 输入
```
4
a
zzaaz
ccff
cbddbb
```
### 输出
```
a
z

bc
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是基于题目中故障按键会使对应字符连续出现两次这一特性，通过遍历字符串来判断哪些字符必然是由正常按键输入的。
- **思路方面**：大多题解都采用遍历字符串，判断相邻字符是否相同的方式。若相邻字符相同，就跳过这两个字符，认为这可能是故障按键产生的；若相邻字符不同，则将该字符对应的按键标记为正常。
- **算法要点**：关键在于对字符串的遍历以及对相邻字符的判断处理，部分题解使用数组或集合来记录正常按键对应的字符。
- **解决难点**：主要难点在于正确理解题目中故障按键的行为模式，并准确实现对字符串的遍历和判断逻辑，同时要注意输出格式需按字母顺序。

### 所选的题解
- **作者：_tommysun_ (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了，通过一个布尔数组 `flag` 记录单独出现的字符，逻辑清晰，可读性强。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s;
        bool flag[26]={0}; 
        for(int len=0;len<s.size();len++){
            if(s[len]==s[len+1]){ 
                len++;
            }
            else flag[s[len]-'a']=1; 
        }
        for(int j=0;j<26;j++){
            if(flag[j]==1) {cout<<char(j+'a');} 
        }
        cout<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：遍历输入字符串，若相邻字符相同则跳过，不同则标记该字符对应按键正常，最后按顺序输出标记为正常的字符。
- **作者：Clyfort (4星)**
    - **关键亮点**：通过详细的例子解释模拟过程，便于理解，并且使用 `set` 维护答案，能自动排序并去重，符合题目按字母顺序输出的要求。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

set <char> ans;

void solve()
{
    ans.clear();
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i ++)
    {
        if (s[i]!= s[i + 1])
            ans.insert(s[i]);
        else
            i ++;
    }
    for (auto c : ans)
        cout << c;
    cout << endl;
}

int main()
{
    int tt = 1;
    cin >> tt;
    while (tt --)
        solve();
    return 0;
}
```
    - **核心实现思想**：遍历字符串，若相邻字符不同则插入 `set` 中，利用 `set` 的特性实现自动排序和去重，最后输出 `set` 中的字符。
- **作者：lianchanghua (4星)**
    - **关键亮点**：先明确指出审题要点，即故障按键只会重复两遍字符，然后通过统计重复字母个数是否为奇数来判断按键是否正常，思路独特。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool f[30];
signed main(){
	ios::sync_with_stdio(false);
    string s;
    int T;
    cin>>T;
    while(T--){
        cin>>s;
        memset(f,0,sizeof(f));
        int l=s.size()-1;
        for(int i=0;i<=l;i++){
        	int j=i;
            while(s[i]==s[j])	j++;//数出重复的个数
            if((j-i)%2==0);
			else				f[s[i]-'a']=1;
			i=j-1;//这里注意：由于i后面要++,所以这里是j-1而不是j
        }
        for(int i=0;i<26;i++)	if(f[i]==1)	cout<<char(i+'a');
        cout<<"\n";
    }
    return 0;
}
```
    - **核心实现思想**：遍历字符串，统计每个字符连续出现的个数，若个数为奇数则标记该字符对应按键正常，最后输出标记为正常的字符。

### 最优关键思路或技巧
利用故障按键会使字符连续出现两次这一特性，通过遍历字符串并判断相邻字符是否相同来确定正常按键。部分题解使用 `set` 或排序去重的方式满足按字母顺序输出的要求，这是在实现过程中的一个实用技巧。

### 拓展
同类型题通常围绕字符处理和特定规则下的判断展开，类似算法套路是根据给定的字符生成规则，通过遍历字符串来分析字符特性，进而解决问题。

### 洛谷相似题目
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：涉及对字符串的处理和校验规则。
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：通过处理字符串统计字符出现次数并按特定格式输出。
- [P1914 小书童——密码](https://www.luogu.com.cn/problem/P1914)：对字符串进行加密解密操作，也是基于字符串处理的题目。 

---
处理用时：67.45秒