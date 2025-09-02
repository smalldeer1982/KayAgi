# [ABC076C] Dubious Document 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc076/tasks/abc076_c

E869120 は、宝物が入ってそうな箱を見つけました。  
 しかし、これには鍵がかかっており、鍵を開けるためには英小文字からなる文字列 $ S $ が必要です。  
 彼は文字列 $ S' $ を見つけ、これは文字列 $ S $ の $ 0 $ 個以上 $ |S| $ 個以内の文字が `?` に置き換わった文字列であることも分かりました。  
 ただし、文字列 $ A $ に対して、$ |A| $ を「文字列 $ A $ の長さ」とします。

そこで、E869120 はヒントとなる紙を見つけました。

- 条件1：文字列 $ S $ の中に連続する部分文字列として英小文字から成る文字列 $ T $ が含まれている。
- 条件2：$ S $ は、条件1を満たす文字列の中で辞書順最小の文字列である。

そのとき、鍵となる文字列 $ S $ を出力しなさい。  
 ただし、そのような文字列 $ S $ が存在しない場合は代わりに `UNRESTORABLE` と出力しなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ |S'|,\ |T|\ \leq\ 50 $
- $ S' $ は英小文字と `?` から成る
- $ T $ は英小文字から成る

### Sample Explanation 1

条件1 を満たす文字列は `atcoder`, `btcoder`, `ctcoder`,..., `ztcoder` の $ 26 $ 個がありますが、その中で最も辞書順で小さいものは `atcoder` なので、$ S\ = $`atcoder` と特定できます。

### Sample Explanation 2

条件1を満たすような文字列 $ S $ が存在しないので、鍵となる文字列 $ S $ は存在しません。

## 样例 #1

### 输入

```
?tc????
coder```

### 输出

```
atcoder```

## 样例 #2

### 输入

```
??p??d??
abc```

### 输出

```
UNRESTORABLE```

# 题解

## 作者：TRZ_2007 (赞：3)

**[题解 AT3600 【[ABC076C] Dubious Document 2】](https://www.luogu.com.cn/problem/AT3600)**  
由于 AtCoder 的端口炸了，所以这份代码是在 AtCoder 上直接提交的，记录详情：
![](https://cdn.luogu.com.cn/upload/image_hosting/open3ksq.png)  

# Solution  
如果这道题目的字符串长度加强一下那这题会变得十分恐怖，但是由于长度都**小于等于50**，所以我们可以考虑**暴力**。  
**怎么暴力呢？** 我们枚举每一个配对情况，看一下是否可以配对，如果可以就看一下是否可以更新答案，最后输出即可。  
看不懂上面文字的（~~应该都看得懂吧~~）我们来看一下这一堆图来加强理解：  
我们以第一组样例为例  
![](https://cdn.luogu.com.cn/upload/image_hosting/mf1cv7qi.png)  
我们发现目标串的对应位置是一个未知元素，因此可以和我们的字符``c``匹配成功，于是指针``j``后移一位。  
![](https://cdn.luogu.com.cn/upload/image_hosting/if3bjykg.png)  
我们发现目标串中是已知元素``t``，不能与``o``进行匹配，所以匹配失败。指针``i``向后移一位，指针``j``复原。  
（一下省略 infinity 张图……）

所以这就是这道题暴力的算法，还是比较简单的，觉得评个黄题是不是过了，给个橙差不多……  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

string ans = "";
string s,t,tmp = "";
int ls,lt,flag;

int main() {
	cin >> s >> t;
	ls = s.size();lt = t.size();
	if(ls < lt)  {	//如果子串比目标串都长，那么肯定失配
		puts("UNRESTORABLE");
		return 0;
	}
	for(int i = 0;i < ls - lt + 1;i++) {
		tmp = s;flag = 0;	//用tmp代替目标串
		for(int j = i;j < i + lt;j++) {
			if(tmp[j] == '?') tmp[j] = t[j - i];	//如果是未知元素，那么匹配
			else {
				if(tmp[j] != t[j - i]) {	//如果不是未知元素且不相等，那么失配
					flag = 1;
					break;
				}
			}
		}
	//	cout << tmp << "\n";
		if(flag == 0) {
			for(int j = 0;j < ls;j++) {	//对于没有匹配到的未知元素附以字典序最小的a
				if(tmp[j] == '?') tmp[j] = 'a';
			}
			if(ans == "") ans = tmp;
			else ans = min(ans,tmp);
		}
	}
	if(ans != "") cout << ans << "\n";
	else puts("UNRESTORABLE");
	return 0;
}
```

---

## 作者：zfn07 (赞：1)

此题虽然看起来很简单，只需枚举即可，但是**有坑**
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t,ans="";//ans为最后的答案，赋为空
int i,j,r;
int main(){
	cin>>s>>t;
	if(s.size()<t.size()){
		cout<<"UNRESTORABLE";
		return 0;
	}//大坑，必须判断s的长度会不会比t小(我被坑了3次QAQ)
	for(i=0;i<=s.size()-t.size();i++){//枚举t从哪个地方开始
		int k=i;//将i替换为k
		string ss=s;//将s替换为ss
		j=0;//初始化为0
		while(j<t.size()){
			if(ss[k]=='?')//如果为'?'，替换
				ss[k]=t[j];
			else if(s[k]!=t[j])//否则，如果不匹配，退出
				break;
			k++;//匹配则继续匹配
			j++;
		}
		if(j==t.size()){//如果完美匹配
			for(r=0;r<ss.size();r++){
				if(ss[r]=='?')//把'?'替换为'a'
					ss[r]='a';
			}
			if(ans=="")//如果ans为空，将ans变为ss
				ans=ss;
			else ans=min(ans,ss);//否则,取字典序最小的
		}
	}
	if(ans=="")//若ans为空
		cout<<"UNRESTORABLE";
	else cout<<ans;//输出ans
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：0)

直接模拟就行。

写一个 `ck(string s, string t)` 判断字符串 $s$ 和题目给定的字符串 $t$ 能否匹配，两个字符串能匹配当且仅当每个元素都相同或一个元素对应的是一个 `?`，注意到 $t$ 就是题目给的 $t$，所以可以保证 $s_i$ 和 $t_i$ 中至少有一个是字母，至多有一个是 `?`。

写一个 `update(string s, string t, int pos)`，三个参数分别是原字符串 $s$，原字符串的子串即题目中的 $t$ 和开始匹配的位置 $pos$，首先是 $[0, pos-1)$ 这一段，这一段并没有被匹配，因此把所有 `?` 换成 `a`（因为要字典序最小），然后将 $[pos, pos + len(t))$ 这一段的 $s_i$ 全部改为 $t_j$，其中 $j = i - pos$，即，把这一段之间换成 $t$，最后将 $[pos+len(t),len(s))$ 这一段所有 `?` 换成 `a`，原因和第一段一样。

然后直接枚举每一个区间，如果可以匹配那就更新最小的字典序的字符串，于是就解决了。


```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)
#define per(i, r, l) for(auto i = (r); i >= (l); i --)

const string wa = "UNRESTORABLE";

bool ck(string s, string t) {
  rep (i, 0, s.size() - 1) {
    if (s[i] != t[i] && s[i] != '?') return 0;
  }
  return 1;
}

string ans, cmp;

void update(string s, string t, int pos) {
  rep (i, 0, pos - 1) if (s[i] == '?') s[i] = 'a';
  rep (i, pos, pos + t.size() - 1) s[i] = t[i - pos];
  rep (i, pos + t.size(), s.size() - 1) if (s[i] == '?') s[i] = 'a';
  if (s < ans) ans = s;
  // cout << ans << endl;
}

void init() {
  ans = "~"; rep (i, 1, 6) ans += ans; cmp = ans;
}

int main() {
  init();
  string s, t; cin >> s >> t;
  int lens = s.size(), lent = t.size();
  if (lens < lent) return printf("%s\n", wa.c_str()), 0;
  rep (i, 0, lens - lent) {
    string k;
    rep (j, i, i + lent - 1) {
      k += s[j];
    }
    if (ck(k, t)) update(s, t, i);
    // cout << ck(k, t);
  }
  if (ans != cmp) printf("%s", ans.c_str()); else printf("%s", wa.c_str());
}
```

---

## 作者：Fengxiang008 (赞：0)

### 题意：
给定 $S$，$T$，$2$ 个字符串，判断 $T$ 字符串是否是 $S$ 的子串，`?` 可以代替任何字符，如果存在，输出 $S$ 的最小字典序的字符串，否则输出 $\texttt{UNRESTORABL}$。

### 思路：

利用 ```set``` 自动排序的特性，构造出多个 $T$ 是 $S$ 子串的字符串，然后挑选字典序最小的即可。

（之前我是想用 KMP 算法，直接判断是否存在子串，然后再进行变化，不过事实证明这样的算法可行性太低，但是自身学习了下 KMP 算法也不错）。

### 代码：

```cpp

#include<algorithm>
#include<iostream>
#include<cstdio>
#include<map>
#include<set>
using namespace std;
string s, t;
set<string> S;
void Work()
{
    int lens = s.size();
    int lent = t.size();
    for(int i = 0; i < lens; i++)
    {
        if(s[i] == '?' || s[i] == t[0])//如果字符相等
        {
            string tmp = s;              //构造判断子串之前的字符
            for(int j = 0; j < i; j++)
                if(tmp[j] == '?')
                    tmp[j] ='a';    
            bool can = false;
            for(int j = 0; j < lent; j++)    //判断是否为子串
            {
 
                if(tmp[i+j]!= '?' && tmp[i+j] != t[j])  //字符匹配
                    break;
                tmp[i+j] = t[j];
                if(j == lent - 1) can = true;
            }
            if(can)
            {
                for(int j = i + lent; j < lens; j++) if(tmp[j] == '?') tmp[j] = 'a';//处理匹配后的字符
                S.insert(tmp);  //压入容器
            }
        }
    }
    if(S.size() == 0) cout << "UNRESTORABLE" << endl;
    else cout << *S.begin() << endl;
}
int main()
{
    cin >> s >> t;
    Work();
    return 0;
}
```



---

## 作者：cjZYZtcl (赞：0)

## 来一发Pascal的题解吧
### 非常不错的字符串练习题
这题就是用字符串暴力。

从后往前枚举每一个放入子串的位置，如果可以放就放进去，然后把其他问号的位置都放上'a'，然后输出就可以了，如果没有可以放的位置就输出'UNRESTORABLE'。

#### 为什么要从后往前？
因为题目说要输出字典序最小的一种，而最后一个可放位置一定是最小的，所以从后往前枚举。
#### 为什么要问号处全部放'a'？
因为'a'是小写字母中字典序最小的，所以问号的地方填'a'可以保证字典序最小。

注意：AT输出要换行！！！
### Code：
```pascal
var
  p:boolean;
  s,x:string;
  i,j:longint;
begin
  readln(s);
  read(x);
  for i:=length(s)-length(x)+1 downto 1 do
  begin
    p:=true;
    for j:=i to i+length(x)-1 do
      if s[j]<>'?' then
        if s[j]<>x[j-i+1] then
        begin
          p:=false;
          break;
        end;
    if p then
    begin
      for j:=1 to i-1 do
        if s[j]='?' then write('a')
                    else write(s[j]);
      write(x);
      for j:=i+length(x) to length(s) do
        if s[j]='?' then write('a')
                    else write(s[j]);
      halt;
    end;
  end;
  writeln('UNRESTORABLE');
end.
```


---

## 作者：Night_sea_64 (赞：0)

本蒟蒻又来写题解了。。。

[AT3600题目传送门](https://www.luogu.com.cn/problem/AT3600)

这道题主要考察的是字符串的操作。

主要思路很简单。就是遍历 $S'$ 的每一位，遍历到 $S'$ 的串长 $-\text{ }T$ 的串长的位置（因为要向后取子串）。然后每一次取从当前位置开始，长度和 $T$ 的串长一样的子串，然后看他和 $T$ 能不能匹配，能匹配，就把 $T$ 的值搬到 $S'$ 里去，然后把 $S'$ 中还是问号的地方全设成 a（因为题目中要求字典序最小）。最后再取每种情况的最小值就可以了。

如果不能理解，那么就看看我的 AC 代码，对一些细节有注释。

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool chk(string a,string b)//判断能否成功匹配
{
	for(int i=0;i<a.size();i++)
		if(a[i]!=b[i]&&a[i]!='?')
			return 0;
	return 1;
}
int main()
{
	string s,t,ans="zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    //把 ans 设为字典序最大的串（串长是 50，不会有更大的串了）
	cin >> s >> t;
	bool flag=0;//flag 表示有没有一种方法能匹配
	for(int i=0;i<=int(s.size())-int(t.size());i++)//size() 返回的不是 int 类型，不把他转成 int 有可能会 RE。
	{
		string temp=s.substr(i,t.size()),now=s;
        //temp 是要判断的子串。now 是复制的 s，因为后面要改，不能直接用 s 来做。
		if(chk(temp,t))
		{
			flag=1;
			for(int j=0;j<t.size();j++)now[i+j]=t[j];//将 now 的相应部分更改为 t。
			for(int j=0;j<now.size();j++)
				if(now[j]=='?')//还有问号，说明不在 t 里，就全部设成 a。
					now[j]='a';
			ans=min(ans,now);
		}
	}
	if(flag)cout << ans << endl;
	else cout << "UNRESTORABLE" << endl;
	return 0;
}
```

蒟蒻题解就到这里。如果对题解内容还不理解，欢迎私信。

**求 dalao 们点个赞再走！！！**

---

