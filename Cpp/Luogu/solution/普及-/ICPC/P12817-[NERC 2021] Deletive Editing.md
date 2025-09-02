# [NERC 2021] Deletive Editing

## 题目描述

Daisy 喜欢玩文字游戏。最近，她一直在和 Daniel 玩一个叫做**删除编辑**的文字游戏。

Daisy 先选择一个单词，例如 $\tt{DETERMINED}$。每一轮游戏中，Daniel 喊出一个字母，例如 $\tt{E}$，然后 Daisy 从单词中**删除该字母的第一次出现**，得到 $\tt{DTERMINED}$。下一轮，Daniel 再次喊出一个字母，例如 $\tt{D}$，Daisy 删除它的第一次出现，得到 $\tt{TERMINED}$。他们继续喊 $\tt{I}$，得到 $\tt{TERMNED}$；喊 $\tt{N}$，得到 $\tt{TERMED}$；喊 $\tt{D}$，得到 $\tt{TERME}$。此时如果 Daniel 喊出字母 $\tt{E}$，Daisy 会得到 $\tt{TRME}$，但如果他们从 $\tt{DETERMINED}$ 开始玩这个游戏，就无法得到单词 $\tt{TERM}$。

Daisy 很好奇，她是否能够从给定的初始单词出发，通过玩若干轮（包括零轮）这个游戏，最终得到她想要的单词。你的任务是帮她判断这一点。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
DETERMINED TRME
DETERMINED TERM
PSEUDOPSEUDOHYPOPARATHYROIDISM PEPA
DEINSTITUTIONALIZATION DONATION
CONTEST CODE
SOLUTION SOLUTION```

### 输出

```
YES
NO
NO
YES
NO
YES```

# 题解

## 作者：Sunrise_up (赞：4)

一道水题。目前[最优解](https://www.luogu.com.cn/record/220642826)。

每次操作只能删除被删除字母的第一次出现，相当于留下字符串每种字母的后若干个，但相对位置不变。所以这题只需 $t$ 从后往前模拟，每次看看 $s$ 有没有保持相对位置的相同的字符就行了。

我们可以使用 STL 模板中的 `rfind` 来实现。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,last,len;
string s,t;
bool f;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//快读 
    cin>>n;
    while(n--){
        cin>>s>>t;
        f=0,len=t.size();//提前存储长度减少访问次数，变快一丢丢 
        for(int i=len-1;i>=0;i--){
        	x=s.rfind(t[i]);//STL 
			if(i+1<len&&last<x||x==string::npos){//绝对位置不同或者找不到
				f=1;
				break;
			}
			last=x,s[x]=1;//不直接删除，虚拟的就行了，快点
		}
        cout<<(f?"NO\n":"YES\n");//三目运算符加快 
    }
    return 0;
}
```

速度快到起飞！

点个赞吧 qwq！

---

## 作者：___define___ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P12817)

## 思路

由于每次操作只能删除被删除字母的第一次出现，所以考虑翻转单词 $s$，再查询单词 $t$ 中每一个字母在翻转后的单词 $s$ 中第一次出现的位置，最后判断这些查询结果是否是升序的即可，注意查询顺序应从单词 $t$ 的结尾开始，否则会使程序出现错误。

这里翻转与查询可以使用 STL 库中自带的 `reverse` 与 `find` 函数，会使程序更加简洁。

## AC Code

```
#include<bits/stdc++.h>
using namespace std;
int n;
string s1,s2;
int a[105];
signed main(){
	scanf("%d",&n);
	while(n--)
	{
		cin>>s1>>s2;
		reverse(s1.begin(),s1.end());
		bool z=0;
		for(int i=s2.size()-1;i>=0;--i)
		{
			a[i]=s1.find(s2[i]);
            if(a[i]!=-1)s1[a[i]]='0';
            else z=1;
			if(i!=s2.size()-1) 
				if(a[i]<a[i+1]) z=1;
		}
		if(!z) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：yongqian123 (赞：1)

## 题目分析
显而易见，$s$ 与 $t$ 完全相同时 `YES`，$s$ 比 $t$ 还短时 `NO`。

```cpp
if (s == t){cout << "YES\n"; continue;}
if (s.size() < t.size()){cout << "NO\n"; continue;}
```

对于其他情况，可以发现，

逆序找 $t_i$ 在 $s$ 的倒序中的位置情况：

```cpp
reverse(s.begin(), s.end());
```

不存在时 `NO`；

如果找到第一个后则删除第一个，那么每次找到的第一个 $t_i$ 升序排列，这是因为每次的 $t_i$ 在 $s$ 的倒序中都必须是第一个出现的 $t_i$，不然后面就无法删除。

```cpp
//<bool in() 函数>
for (int i = t.size() - 1, _pos = 0; i >= 0; i--){
	int pos = s.find(t[i]);
	if (pos == string::npos) return 0;
	if (pos < _pos) return 0;
	s[_pos = pos] = ' ';
}return 1;
```

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
int n;
string s, t;
bool in(){
	reverse(s.begin(), s.end());
	for (int i = t.size() - 1, _pos = 0; i >= 0; i--){
		int pos = s.find(t[i]);
		if (pos == string::npos) return 0;
		if (pos < _pos) return 0;
		s[_pos = pos] = ' ';
	}return 1;
}
signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	while (n--){
		cin >> s >> t;
		if (s == t){cout << "YES\n"; continue;}
		if (s.size() < t.size()){cout << "NO\n"; continue;}
		if (in()) cout << "YES\n";
		else cout << "NO\n";
	}return 0;
}

```

---

## 作者：_seven_7k_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12817)
## 思路
首先看看题面，这道题其实是一个模拟题，每喊一个字母，删除的都是第一个出现在字符串的相同字母，要求删到和第二个字符串相同。  
我们可以这么想：从第一个字符串末尾开始判定，定义一个 $u$，$u$ 赋值第二个字符串长度。设第一个字符串为 $a$，第二个字符串为 $b$，当 $a[i]=b[u]$ 时，$u$ 减一。  
那么，我们如何判定是否可以呢？我们不难发现，当 $a[i]=b[u]$ 且 $a[i]$ 在之前出现过，那么这个字符串就无法得到想要的单词（因为是删除第一个字母，所以会删除当前字母，保留之前出现过的字母，这样就不符合题意）或者判定完后，$u$ 不为 $-1$，也是无法得到想要的单词。针对第一种情况，我们可以定义一个数组 $flag$，用来判定当前字母是否在之前出现过。针对第二种情况，我们只要加一个判断就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int flag[27];
int main(){
	int n,l=0;
	cin>>n;
	int i,j;
	for(i=1;i<=n;i++){
		cin>>a>>b;
		for(int j=0;j<26;j++){
			flag[j]=0;
		}
		int u=b.size()-1;
		l=1;
		for(int j=a.size()-1;j>=0;j--){
			
			if(a[j]!=b[u]){
				flag[a[j]-'A']=1;
			}
			else{
				if(flag[a[j]-'A']==1){
					cout<<"NO"<<endl;
					l=0;
					break;
				}
				u--;
			}
			if(u==-1){
				break;
			}
		}
		if(u==-1){
			cout<<"YES"<<endl;
		}
		else if(l){
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Firsry (赞：0)

# P12817 [NERC 2021] Deletive Editing

> Daisy 从单词中**删除该字母的第一次出现**，她是否能够从给定的初始单词出发，通过玩若干轮（包括零轮）这个游戏，最终得到她想要的单词。

- 不在 $t$ 内的字母可以任意依次删去，此时得到一个只含有想要单词内字母的字符串 $s'$。
- 对于 $s'$，唯一的操作是从前向后删去字母，所以找到的结果 $t$ 一定是在结尾。所以让 $s',t$ 逐个末位相比对，匹配的就在 $t$ 中进行 `pop_back` 操作，更新当前任务为次末尾字符。
- 如果在从后向前扫描 $s'$时，一个在 $t$ 中出现了的字母却并不在 $t$ 的末尾，是不合法的。即使前面出现了 $t$，也会因为当前字符出现在后面无法删除。

用题干中的例子：`deTeRMinEd,determinEd`，很好理解了。

所以就两点：存在，按序。实现的时候并不会去构造 $s'$ 字符串，只要代入 $t$ 查找一下即可。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;
string s, t, tmp;

inline bool check(string str, char ch) {
	for (char c : str)
		if (c == ch)
			return true;
	return false;
}

int main() {
	scanf("%d", &n);
	while (n--) {
		bool flag = true;
		cin >> s >> t, tmp.clear();
		for (int i = s.size() - 1; i >= 0; --i)
			if (check(t, s[i])) {
				if (t.back() == s[i])
					t.pop_back();
				else
					flag = false, i = -1;
			}
		if (flag && t.empty())
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
```

花絮：qaq 编辑字符串也是 `edit`。

---

## 作者：lvweisi (赞：0)

### 题目大意：
给出两个不超过 $30$ 长度且保证都是大写英文字母的字符串，问能不能重复删掉某个第一次出现的字母后的第一个字符串和第二个字符串是一样的。
### 解题思路：
由于测试用例和字符串长度比较小，考虑用模拟解决。对于第二个字符串的每一个位置的字符，需要保证其在第一个字符串的位置后面没有跟他重复的字符，所以只需要将两个字符串倒过来进行一一匹配，如果当前对应的字母在前方出现，那么就是错误的，否则则进行特判，若当前的这个第二个字符串的长度比第一个的小，且匹配完成那么就输出 `YES`。
### 代码如下：
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char A[100],B[100];
char a[100],b[100];
int t[30];//纪录前面是否出现过了
int main(){
	cin>>n;
	while(n--){
		cin>>A>>B;
		for(int i=0;i<=27;i++)t[i]=0;//多测记得要清空
		int l=strlen(A);
		int l1=strlen(B);
		if(l<l1){
			cout<<"NO"<<'\n';
			continue;
		}
		for(int i=0;i<l;i++)a[i]=A[l-i-1];
		for(int i=0;i<l1;i++)b[i]=B[l1-i-1];//翻转字符串
		int pd=0;
		int j=0;
		for(int i=0;i<l;i++){
			if(a[i]==b[j]){
				if(t[a[i]-'A']!=0){
					pd=1;
					break;
				}
				j++;
				if(j==l1)break;
			}
			else t[a[i]-'A']=1;
		}
		if(pd==1||j<l1)cout<<"NO"<<'\n';
		else cout<<"YES"<<'\n';
	}
	return 0;
}
```

---

## 作者：TONY_LIU0831 (赞：0)

## 题目大意
有 $n$ 组数据，在每一组数据中给定两个字符串，问能否在第一个字符串中用多次**删除某字母的第一次出现**操作使第一个字符串变为第二个字符串。
## 解题思路
由于操作只会删除某字母的第一次出现，所以答案与第一个字符串的前部分无关。可以先翻转两个字符串。接着再依次查找第二个字符串的**每一个**字符在第一个字符串中的位置，只要位置按**升序**排列，就可以变成第二个字符串。
## 注意事项
查完字符的位置后应将第一个字符串中**对应位置**的字符设成除**大写字母以外**的字符，这样做是为了防止第二个字符串中相同的字符查找到同一个位置。
## 代码（含注释）
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    while(n--){
        int last = 0, now = 0;  //用两个变量记录位置可以节省一个数组
        bool isno = false;
        string str1,str2;
        cin >> str1 >> str2;
        reverse(str1.begin(),str1.end());  //翻转
        reverse(str2.begin(),str2.end());
        for(int i = 0;i < str2.length();++i){
            now = str1.find_first_of(str2[i]);  //查找位置
            if(now == -1 || (last > now)){  //如果找不到或位置不升序
                cout << "NO" << endl;
                isno = true;
                break;
            }
            str1[now] = '-';  //将第一个字符串中对应位置设成 -
            last = now;
        }
        if(!isno) cout << "YES" << endl;
    }
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/220549820)

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12817)
## 题目分析
希望审核大大给过。

这是一道考我们**字符串的应用**。由于每次操作只能删除被删除字母的第一次出现，所以可以翻转字符串 $s1$ 进行操作，定义一个数组记录 $s1$ 字符串中每一个 $s2$ 字符出现的位置，并且删掉该字符。如果升序，便可以实现，反之则不可以实现。（这些操作可以使用 std 中自带的 `reverse`、`find`、`erase` 来解决）

下面是本题目的代码。
## 题目[代码](https://www.luogu.com.cn/record/220538891)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
int n,a[31];
signed main() {
	speed
	cin>>n;
	while(n--){
		memset(a,0,sizeof(a));
		bool flag=0;
		string s1,s2;
		cin>>s1>>s2;
		reverse(s1.begin(),s1.end());
		for(int i=s2.size()-1;i>=0;i--){
			a[i]=s1.find(s2[i]);
			if(a[i]!=-1)s1.erase(a[i],1);
			else flag=1;
			if(i!=s2.size()-1) 
				if(a[i]<a[i+1]) flag=1;
		}
		if(flag)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
//求关注qwq，一定回关！
```

---

