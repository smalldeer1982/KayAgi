# [GCJ Farewell Round #1] Colliding Encoding

## 题目描述

**Alan** 今天在学校上了第一节密码学课程。他决定运用所学知识，设计自己的加密方式。他计划将字母 `A` 到 `Z` 分别映射到十进制数字 $0$ 到 $9$。然后，他会将每个单词中的字母替换为对应的数字，从而将单词编码为一个由数字组成的字符串。

由于过于兴奋，**Alan** 没有注意到英文字母共有 $26$ 个，而十进制数字只有 $10$ 个。因此，可能会出现**碰撞**，即不同的单词被编码为相同的字符串。

给定 **Alan** 想要编码的 $N$ 个单词及其使用的映射规则，请判断列表中是否存在至少一对单词会发生碰撞。

## 说明/提示

**样例解释**

在样例 #1 中，`A` 映射为 $0$，`B` 为 $1$，`C` 为 $2$，`D` 为 $3$，`E` 为 $3$。此时，`ABC` 编码为 $012$，`BC` 为 $12$，`BCD` 为 $123$，`CDE` 为 $233$。由于所有编码均不同，因此没有碰撞。

在样例 #2 中，`C` 映射为 $2$，`D` 为 $3$，`E` 为 $3$，`F` 为 $3$，`G` 为 $3$。此时，`CDE` 编码为 $233$，`DEF` 和 `EFG` 均为 $333$。由于 `DEF` 和 `EFG` 的编码相同，因此存在碰撞。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- 对于所有 $\alpha$，$0 \leq \mathbf{D}_{\alpha} \leq 9$。
- 对于所有 $i$，$1 \leq \mathbf{S}_{i}$ 的长度 $\leq 10$。
- 对于所有 $i$，$\mathbf{S}_{i}$ 的每个字符均为大写字母 `A` 到 `Z`。
- 对于所有 $i \neq j$，$\mathbf{S}_{i} \neq \mathbf{S}_{j}$。

**测试集 1（4 分，可见判定）**

- $1 \leq \mathbf{N} \leq 100$。

**测试集 2（10 分，可见判定）**

- $1 \leq \mathbf{N} \leq 6 \times 10^{4}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
0 1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
4
ABC
BC
BCD
CDE
0 1 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
3
CDE
DEF
EFG```

### 输出

```
Case #1: NO
Case #2: YES```

# 题解

## 作者：蒟蒻whker (赞：2)

简单模拟题。STL 大法好！  

按照题意，将每个由字母构成的字符串 $S$ 转化为由数字构成的字符串。随后使用 map 存储，检测是否重复即可。

时间复杂度 $O(TNL)$，$20$ 秒轻松跑完（其中 $L$ 指字符串的最大长度）。

**注意**：如果你一边输入一边转化字符串，在找到一组碰撞的字符串时不能直接退出循环，否则将导致输入错位。

详见代码。
### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
map<string,bool>mp;//mp[S]表示该字符串是否出现过
int main(){
	int T;
	cin>>T;
	for(int v=1;v<=T;v++){
		int num[30]={};
		mp.clear();//多测不清空，爆零两行泪
		for(int i=0;i<26;i++)cin>>num[i];//每一个字符对应的数字
		int n;
		cin>>n;
		bool flag=0;//记录是否有碰撞
		while(n--){
			string s;
			cin>>s;
			if(flag)continue;
			for(int i=0;i<s.size();i++){
				s[i]=num[s[i]-'A']+'0';//根据输入将字母构成的字符串转化为由数字构成的字符串
			}
			if(mp[s]==true){
				flag=1;//不能break，否则输入会错位
			}
			else mp[s]=true;
		}
		if(!flag){
			printf("Case #%d: NO\n",v);
		}
		else{
			printf("Case #%d: YES\n",v);
		}
	}
	return 0;
}
```
求一键三连~

---

## 作者：Clare613 (赞：2)

bushi，这道题目怎么时限那么大。
## 思路：
这道题很简单，我们只需要做两件事：
1. 转成编码。
2. 判断之前是否出现过。

那么这里我就先节选以下转成编码步骤：
```cpp
string num="";
for(int i=0;i<x.size();++i){
	num=num+d[x[i]-'A'+1];
}
```
看上去很简单，但是要注意前导零是要有的，不然就会寄。\
接着就是 map 来判重，没什么难度，这就不展示了，看总代码吧。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
char d[27];
unordered_map<string,int> a;
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0)->sync_with_stdio(0);
	int T;
	cin>>T;
	for(int id=1;id<=T;++id){
		a.clear();
		for(int i=1;i<=26;++i){
			cin>>d[i];
		}
		int n;
		cin>>n;
		bool flag=0;
		for(int i=1;i<=n;++i){
			string x;
			cin>>x;
			string num="";
			for(int i=0;i<x.size();++i){
				num=num+d[x[i]-'A'+1];
			}
			if(a[num]==1) flag=1;
			a[num]=1;
		}
		if(flag) cout<<"Case #"<<id<<": YES\n";
		else cout<<"Case #"<<id<<": NO\n";
	}
	return 0;
}
```

---

## 作者：AnOIer (赞：1)

输入一个单词后枚举每个字母，让转换后的数字字符串加上这个字母对应的数字转换成的字符串。

然后，将转换后的数字字符串用桶标记为 $1$，这样如果后面的字符串转换后的结果在桶中已经有值时，则认为产生碰撞。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[30];
map<string,bool> t;
int main(){
	int T,k=0;
	cin>>T;
	while(T--) {
		for(int i=1;i<=26;i++) cin>>a[i];
		int q;
		cin>>q;
		bool f=1;
		t.clear();
		while(q--) {
			string w,p="";
			cin>>w;
			for(int i=0;i<w.size();i++) {
				p+=to_string(a[(w[i]-'A'+1)]);
			}
			if(t[p]) { //已经有了，即产生碰撞
				f=0;	
			}else t[p]=1; //没有产生碰撞则把值设为1
		} 
		if(f) {
			cout<<"Case #"<<++k<<": NO\n";
		}else {
			cout<<"Case #"<<++k<<": YES\n";
		}
	} 
	return 0;
}

```

---

## 作者：jsisonx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12946)

# 题目分析

首先，题目问是否存在相同的编码，而输入的是 $n$ 个字符串，所以无论如何，第一步要将所有字符串转化为数字的编码。这是第一步，也是最重要的一步。由于字符串长度小于等于 $10$，$D_i$ 小于等于 $9$，因此完全可以将每一个编码用十进制数字存储。这样做的好处是，判断是否有重复的时候可以先对所有编码排序，然后比较相邻两个编码即可。

注意，转换成数字后可能存在被忽略的前导零，于是排序时先对字符串长度排序，字符串长度相同再比较编码大小即可解决。

# 代码


```cpp
#include<bits/stdc++.h>
#define N 1000001
using namespace std;
struct bm{
	long long code1;
	int size1;
}str[N];
long long code[N];
int num[26],Size[N];
int cmp(bm x,bm y){
	if(x.size1!=y.size1){
		return x.size1>y.size1;
	}
	return x.code1>y.code1;
}
int main(){
	int t,t0=1;
	cin>>t;
	while(t--){
		int n;
		memset(code,0,sizeof(code));
		memset(Size,0,sizeof(Size));
		for(int i=0;i<26;i++){
			cin>>num[i];
		}
		cin>>n;
		for(int i=1;i<=n;i++){
			char c[15];
			cin>>c;
			int len=strlen(c);
			for(int j=0;j<len;j++){
				code[i]=code[i]*10+num[c[j]-'A'];
				Size[i]++;
				str[i].code1=code[i];
				str[i].size1=Size[i];
			}
		}
		sort(str+1,str+1+n,cmp);
		cout<<"Case #"<<t0<<": ";
		int yes=0;
		for(int i=1;i<n;i++){
			if(str[i].code1==str[i+1].code1&&str[i].size1==str[i+1].size1){
				cout<<"YES"<<endl;
				yes=1;
				break;
			}
		}
		if(!yes){
			cout<<"NO"<<endl;
		}
		t0++;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P12946)

### 前言

这道题考察的是如何将字母映射到数字后，判断给定的单词列表中是否存在编码相同的不同单词。关键在于高效地处理映射和检测重复的编码。

### 思路

我们可以先根据给定的映射规则将每个字母转换成对应的数字，然后把每个单词转换成数字字符串。接着，通过排序和比较相邻字符串的方式，检查是否存在重复的编码，从而判断是否有碰撞发生。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void sv() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        vector<int> m(26);
        for (int i = 0; i < 26; ++i) {
            cin >> m[i];
        }
        int N;
        cin >> N;
        vector<string> ec(N);
        for (int i = 0; i < N; ++i) {
            string w;
            cin >> w;
            string cc;
            for (char c : w) {
                cc += to_string(m[c - 'A']);
            }
            ec[i] = cc;
        }
        sort(ec.begin(), ec.end());
        bool cl = false;
        for (int i = 1; i < N; ++i) {
            if (ec[i] == ec[i - 1]) {
                cl = true;
                break;
            }
        }
        cout << "Case #" << t << ": " << (cl ? "YES" : "NO") << endl;
    }
}

int main() {
    sv();
    return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：1)

又是水题的一天。

我们只要把输入的字符串 $S$ 对印每一个字符 $\alpha$ 的数字形式，然后用一个映射 map 即可。

总的来说就是 map 套 map。

时间复杂度 $O(TNS)≈O(6\times10^7)$。

## 代码           

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int f=t;
    while(t--){
        map<char,char>ab;
        map<string,int>mp;
        for(int i=1;i<=26;i++){
            char x;
            cin>>x;
            ab['A'-1+i]=x;
        }
        int n;
        cin>>n;
        string ans="NO";
        for(int i=1;i<=n;i++){
            string s;
            cin>>s;
            int len=s.size();
            string s1="";
            for(int j=0;j<len;j++){
                s1+=ab[s[j]];
            }
            mp[s1]++;
            if(mp[s1]>1)ans="YES";
        }
        cout<<"Case #"<<f-t<<": "<<ans<<"\n";
    }
    
    return 0;
}
```

---

## 作者：zhoujunchen (赞：1)

首先将给定的字符串转为编码。



```cpp
for(auto c:s)res=res+to_string(a[c-'A']);
```

$a$ 为映射规则。

然后判断编码中有没有重复的，我用的 set。


```cpp
if(st.count(res))flag=0;
st.insert(res); 
```

输出有点恶心。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[91],sbs;
inline void man(){
    bool flag=1;
	sbs++;
	for(int i=0;i<26;i++)cin>>a[i];
	cin>>n;
	set<string> st;
	for(int i=1;i<=n;i++){
		string s,res="";
		cin>>s;
		for(auto c:s)res=res+to_string(a[c-'A']);
		if(st.count(res))flag=0;
		st.insert(res); 
	}
	cout<<"Case #"<<sbs<<": "<<(flag?"NO":"YES")<<"\n";
} 
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--)man();
	return 0;
}
```

---

## 作者：dashabi35 (赞：0)

这道题是一道十分入门的题目。

前 $26$ 个字母直接用数组映射就行了，然后处理完的字符串可以用 ```map``` 映射，当然 ```unordered_map``` 在这里会快很多，其他地方主要看细心，细节详见代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
char a[30],s[15];
string make;
unordered_map<string,bool> mp;
bool flag;
int main()
{
	scanf("%d",&T);
	for(int c=1;c<=T;++c)
	{
		mp.clear();
		flag=0;
		for(int i=0;i<26;++i)
		{
			int t;
			scanf("%d",&t);
			a[i]='0'+t;
		}
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			scanf("%s",s);
			make.clear();
			for(int j=0;s[j]!='\0';++j)
			{
				make+=a[s[j]-'A'];
			}
			if(mp[make]) flag=1;
			else mp[make]=1;
		}
		printf("Case #%d: %s\n",c,flag?"YES":"NO");
	}
	return 0;
}
```
也是抢到最优解了好吧，拉爆第二名。

---

