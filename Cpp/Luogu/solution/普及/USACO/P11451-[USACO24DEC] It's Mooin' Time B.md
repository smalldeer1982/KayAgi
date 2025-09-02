# [USACO24DEC] It's Mooin' Time B

## 题目描述

Farmer John 正在试图向 Elsie 描述他最喜欢的 USACO 竞赛，但她很难理解为什么他这么喜欢它。他说「竞赛中我最喜欢的部分是 Bessie 说 『现在是哞哞时间』并在整个竞赛中一直哞哞叫」。

Elsie 仍然不理解，所以 Farmer John 将竞赛以文本文件形式下载，并试图解释他的意思。竞赛被定义为一个长度为 $N$（$3≤N≤20000$）的小写字母字符串。一种哞叫一般地定义为子串 $c_ic_jc_j$，其中某字符 $c_i$ 之后紧跟着 $2$ 个某字符 $c_j$，且 $c_i≠c_j$。根据 Farmer John 的说法，Bessie 哞叫了很多，所以如果某种哞叫在竞赛中出现了至少 $F$（$1≤F≤N$）次，那可能就是 Bessie 发出的。

然而，Farmer John 的下载可能损坏，文本文件可能存在至多一个字符与原始文件不同。将可能的误差考虑在内，输出所有可能是 Bessie 发出的哞叫，按字典序顺序排序。

## 说明/提示

### 样例 #1 解释

在这个样例中，任何字符变化都不会影响答案。唯一 Bessie 可能发出的哞叫是 $\tt{moo}$。

### 样例 #2 解释

在这个样例中，位置 $8$（从零开始索引）的 $\tt{a}$ 可能是由 $\tt b$ 损坏导致的，这使得 $\tt baa$ 成为一种 Bessie 发出两次的可能的哞叫。此外，位置 $11$ 的 $\tt q$ 可能是由 $\tt c$ 损坏导致的，这使得 $\tt cqq$ 成为一种 Bessie 可能的哞叫。$\tt aqq$ 可以通过将 $\tt c$ 换成 $\tt a$ 来达到。

### 测试点性质
- 测试点 1-3：样例。
- 测试点 4-8：$N≤100$。
- 测试点 9-13：没有额外限制。

## 样例 #1

### 输入

```
10 2
zzmoozzmoo```

### 输出

```
1
moo```

## 样例 #2

### 输入

```
17 2
momoobaaaaaqqqcqq```

### 输出

```
3
aqq
baa
cqq```

## 样例 #3

### 输入

```
3 1
ooo```

### 输出

```
25
aoo
boo
coo
doo
eoo
foo
goo
hoo
ioo
joo
koo
loo
moo
noo
poo
qoo
roo
soo
too
uoo
voo
woo
xoo
yoo
zoo```

# 题解

## 作者：WZWZWZWY (赞：17)

~~好恶臭的题号哼哼哼啊啊啊啊啊~~（

前置：大佬的 [string 函数用法](https://blog.csdn.net/kumoue/article/details/123851809)。

本题有两种思路。



------------

#### 第一种：

一种是**对于每一个位置**，判断能否和后两个位置组成一种声音，和更改一个字符后组成的声音，然后统计所有声音出现的次数。

这种写法需要考虑的细节比较多。

```cpp
#include <bits/stdc++.h>
using namespace std;

map <string, int> mp;
map <string, bool> can; // 更改一个字符后可以组成的哞声 

vector <string> ans;

signed main() {
    //cin.tie(0); ios::sync_with_stdio(0);
    int n, f; cin >> n >> f;
    string s; cin >> s;
    for (int i = 0; i < n - 2; i++) {
    	string s1, s2, s3;
		s1 = s[i]; s2 = s[i + 1]; s3 = s[i + 2];
		
     	if (s[i] != s[i + 1] && s[i + 1] == s[i + 2]) {
			for (char j = 'a'; j <= 'z'; j++) {
				string v = string(1, j) + s2 + s3;
				if (v == s1 + s2 + s3) continue;
				string lst = string(1,s[i-2])+string(1,s[i-1])+string(1,s[i]);
				string lst2 = string(1,s[i-1])+string(1,s[i])+string(1,s[i+1]);
				if (j != s[i + 1] && v != lst && v != lst2) can[v] = 1, mp[v];
			}
     		mp[s1 + s2 + s3] ++;
		 }
		else if (s[i + 1] == s[i + 2]) 
			for (char j = 'a'; j <= 'z'; j++) {
				string v = string(1, j) + s2 + s3;
				string lst = string(1,s[i-2])+string(1,s[i-1])+string(1,s[i]);
				string lst2 = string(1,s[i-1])+string(1,s[i])+string(1,s[i+1]);
				if (j != s[i + 1] && v != lst && v != lst2) can[v] = 1, mp[v];
			}
		else { // s[i + 1] != s[i + 2]
			string nxt = string(s, i + 1, 3);
			string nxt2 = string(s, i + 2, 3);
			string now1 = s1 + s3 + s3;
			string now2 = s1 + s2 + s2;
			if (s[i] != s[i + 1] && nxt2 != now2) can[now2] = 1, mp[now1];
			if (s[i] != s[i + 2] && nxt != now1) can[now1] = 1, mp[now1];
		}
	}

	for (auto u : mp) 
		if (u.second + can[u.first] >= f) ans.push_back(u.first);
		
	cout << ans.size() << "\n";
	sort(ans.begin(), ans.end());
	for (auto u : ans) cout << u << "\n";
	return 0;
}
```


------------

#### 第二种：

第二种是**对于每一种声音**（将其命名为 $moo$ 吧），统计出现次数。

注意，如果 $\overline{s_{i+1}s_{i+2}s_{i+3}}$ 或者 $\overline{s_{i+2}s_{i+3}s_{i+4}}$ 能构成 $moo$，就不要更改 $\overline{s_{i}s_{i+1}s_{i+2}}$ 的值使得它为 $moo$，因为这样会浪费修改次数。

这种比较好写一些。

```cpp
#include <bits/stdc++.h>
using namespace std;

vector <string> ans;

int diff(string a, string b) {
	int n = a.size(), cnt = 0;
	for (int i = 0; i < n; i++) cnt += (a[i] != b[i]);
	return cnt;
}

signed main() {
    //cin.tie(0); ios::sync_with_stdio(0);
    int n, f; cin >> n >> f;
    char str[114514]; cin >> str;
    for (char a = 'a'; a <= 'z'; a++)
    	for (char b = 'a'; b <= 'z'; b++) {
    		if (a == b) continue;
    		string moo = string(1, a) + string(2, b), s(str);
    		int change = 1, cnt = 0;
    		
    		for (int i = 0; i < n - 2; i++) {
    			string v = string(s, i, 3);
    			if (v == moo) cnt ++, i += 2;
    			else if (diff(v, moo) <= 1 && change && string(s, i + 1, 3) != moo
					&& string(s, i + 2, 3) != moo) { // 仅相差一位 
    				cnt ++;
    				for (int j = 0; j < 3; j++)
    					if (s[i + j] != moo[j]) s[i + j] = moo[j];
    				change --;
				}
			}
			if (cnt >= f) ans.push_back(moo);
		}
	
	cout << ans.size() << "\n";
	sort(ans.begin(), ans.end());
	for (auto u : ans) cout << u << "\n";
	return 0;
}
```

感觉这么简单的题没什么好说的？还有什么问题或建议就发在评论区吧。

可以催我把代码注释补上。

---

## 作者：GZXUEXUE (赞：10)

### 思路

注意到 $n \le 20000$，考虑直接暴力。每次枚举**合法的（$c_i \ne c_j$）** $c_i$ 和 $c_j$，然后对「竞赛」字符串进行判断。

我们遍历查找每一个「哞哞叫」字符串在「竞赛」字符串中出现了多少次：

- 如果出现次数大于等于 $F$，那么这个「哞哞叫」字符串就是正确的。

- 如果出现次数刚好等于 $F - 1$，那么考虑「竞赛」字符串损坏了。我们再遍历一次「竞赛」字符串，如果修改一个**之前没有用过的**字符可以变成这个「哞哞叫」字符串，那么这个「哞哞叫」字符串就是正确的。

该算法时间复杂度为 $O(m^2N)$，其中 $m = 26$。

### 实现

```cpp
# include <iostream>
# include <cstring>
# include <vector>
using namespace std;
int f; string p; // p表示「竞赛」字符串
vector<string> v; // 使用vector记录正确的「哞哞叫」字符串
bool check(string s){ // s表示这个「哞哞叫」字符串
	bool flag[20005] = {false}; // 记录这个字符有没有用过。
	int cnt = 0; // 记录这个「哞哞叫」字符串在「竞赛」字符串中出现了多少次
	for (int i = 0;i <= p.size() - 3;i++){
		if (p[i] == s[0] && p[i+1] == s[1] && p[i+2] == s[2] && !flag[i] && !flag[i+1] && !flag[i+2]){ // 如果这段就是s
            // 记录
			cnt++;
			flag[i] = flag[i+1] = flag[i+2] = true; // 这三个字符用过了
			if (cnt >= f) return true; // 如果已经“叫够了”那么s一定是正确的
		}
	}if (cnt + 1 == f){ // 如果出现次数刚好等于f - 1，那么考虑「竞赛」字符串损坏了。
        // 查找之前没有用过的可以变成s的连续字符
		for (int i = 0;i <= p.size() - 3;i++){
			if (p[i] == s[0] && !flag[i+2] && p[i+1] == s[2]) return true;
			if (p[i] == s[0] && !flag[i+1] && p[i+2] == s[2]) return true;
			if (p[i+1] == s[1] && !flag[i] && p[i+2] == s[2]) return true;
		}
	}return false;
}int main(){
	cin >> f >> f >> p;
    // 循环枚举ci,cj
	for (char ci = 'a';ci <= 'z';ci++){
		for (char cj = 'a';cj <= 'z';cj++){
			if (ci == cj) continue; // 注意ci不等于cj
			string now = ""; // 把ci,cj拼合成「哞哞叫」字符串
			now = now + ci; now = now + cj; now = now + cj;
			if (check(now)) v.push_back(now); // 加入正确的一种「哞哞叫」字符串
		}
	}cout << v.size() << endl; // 输出个数
	for (int i = 0;i < v.size();i++) cout << v[i] << endl; // 输出可能的「哞哞叫」字符串
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：8)

P11451，好有寓意的题目编号。

我们注意到要选形似 $\texttt{abb}$ 的形式，而题目中全是小写字母，所以考虑枚举上面的 $\texttt{a}$ 和 $\texttt{b}$。

然后我接下来就是一个贪心，假如枚举到了 $\texttt{abb}$，假如在字符串中遇到了 $\texttt{abb}$，那么出现次数 $+1$，假如遇到了 $\texttt{abx}$，那么要分讨一下：

- 接下来出现了 $\texttt{ababb}$，那么用掉修改次数显然不优，不如不用。
- 否则直接用，因为用掉对出现次数的增加量最多为 $1$。

同理，若遇到了 $\texttt{axb}$，若接下出现的是 $\texttt{aabb}$，那么不用修改次数，否则用。而遇到 $\texttt{xbb}$ 直接用掉。

时间复杂度 $O(|S|^2n)$，其中 $S$ 为字符集。

---

## 作者：masonxiong (赞：5)

# 暴力

首先暴力是好想的，我们枚举更改的位置，然后枚举这个位置改成的字符，然后每次扫一遍统计一下有哪些字符串满足要求，最后统计答案并输出，时间复杂度是 $O(n^2m)$，其中 $m$ 是字符集大小。

如果评测机性能足够强大并且你的常数足够小，这个量级说不定真能跑过去（）


```cpp
#include <bits/stdc++.h>
using namespace std;

int n, f;
string s, t;
set<string> answer;

void updateAnswer() {
	map<string, int> eCount;
	for (size_t i = 0; i + 2 < t.size(); i++)
		if (t[i] != t[i + 1] && t[i + 1] == t[i + 2])
			eCount[t.substr(i, 3)]++;
	for (auto i : eCount)
		if (i.second >= f)
			answer.insert(i.first);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> f >> s, t = s;
	updateAnswer();
	for (int i = 0; i < n; i++) {
		for (t[i] = 'a'; t[i] <= 'z'; t[i]++)
			if (t[i] != s[i])
				updateAnswer();
		t[i] = s[i];
	}
	cout << answer.size() << '\n';
	for (auto i : answer)
		cout << i << '\n';
    return 0;
}
```


# 正解

为什么暴力时间复杂度不优，是因为：你每次只修改一个点，修改这一个点所影响的子串数量极其有限，而你却把整个字符串都扫了一遍。

那么我们不妨先提前扫一边，统计每一种子串的出现次数。首先如果有字符串在不更改字符的情况下就满足条件的话肯定是被统计到答案里的。

然后我们像暴力一样枚举，修改位置 $i$ 之后会对下面这些子串产生影响：$s_{[i-2\dots i]},s_{[i-1\dots i+1]},s_{[i\dots i+2]}$。

我们分别看这三个新子串，若某一个子串之前出现了 $F-1$ 次，并且之前的出现位置和现在的出现位置不相交，那么这个子串就会被统计到答案里。这样就可以优化掉一个 $n$ 的时间复杂度。


```cpp
#include <bits/stdc++.h>
using namespace std;

int n, f;
string s, t;
map<string, set<int>> cnt;
set<string> answer;

void updateAnswer(size_t j) {
	auto v = cnt[s.substr(j, 3)];
	if (v.size() == f - 1 && v.count(j - 1) == 0 && v.count(j - 2) == 0 && v.count(j + 1) == 0 && v.count(j + 2) == 0)
		answer.insert(s.substr(j, 3));
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> f >> s, t = s;
	for (int i = 0; i + 2 < s.size(); i++)
		if (s[i] != s[i + 1] && s[i + 1] == s[i + 2])
			cnt[s.substr(i, 3)].insert(i);
	for (auto i : cnt)
		if (i.second.size() >= f)
			answer.insert(i.first);
	for (int i = 0; i < s.size(); i++) {
		for (s[i] = 'a'; s[i] <= 'z'; s[i]++)
			if (s[i] != t[i])
				for (int j = i - 2; j <= i; j++)
					if (0 <= j && j + 2 < s.size())
						if (s[j] != s[j + 1] && s[j + 1] == s[j + 2])
							updateAnswer(j);
		s[i] = t[i];
	}
	cout << answer.size() << '\n';
	for (auto i : answer)
		cout << i << '\n';
	return 0;
}
```

---

## 作者：orpg (赞：4)

## 思路
看到 $3≤N≤20000$，暗示这题不能出现平方，不然肯定超时。

不难想到可以先遍历一边字符串，找出在不修改情况下，一共有多少个 $c_ic_jc_j$ 然后用 map 和数组记录有多少个不同的 $c_ic_jc_j$ 和它们分别出现了多少次。

下一步，我们遍历一遍所有的 $c_ic_jc_j$ 看看有没有自身已经满足要求的，记录答案并且标记，避免在接下来的修改操作中重复记录。

然后对于每一种独特的 $c_ic_jc_j$ 我们都遍历一次字符串并截下长度为 3 的子串，判断其是否能通过修改变成 $c_ic_jc_j$ 和 $c_ic_jc_j$ 的数量是否大于等于 $F-1$ 因为一次修改最多只能让 $c_ic_jc_j$ 的数量增加一个。如果可以，我们还需要判断是否会跟之前每一个 $c_ic_jc_j$ 重叠。

如果以上都可以则更新答案。

最后排序所以答案，按字典序输出。

Tip：需要特判，否则第三个点会 WA。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f;
string s;
map<string,int> mp; 
map<string,int> vis[20001];
map<string,int> vis1;
string mp1[20005];
int cnt1=0;
string ans[20005];
int cnt=0;
bool check(string a,string b){
	if(a[0]==b[0]){
		if(a[1]==b[1]&&a[2]!=b[2]) return true;
		if(a[2]==b[2]&&a[1]!=b[1]) return true;
	} 
	else if(a[0]!=b[0]){
		if(a[2]==b[2]&&a[1]==b[1]) return true;
	}
	return false;
}
bool pos(int x,int y){
	int x1=min(x+2,n);
	int y1=min(y+2,n);
	if(x<=y&&y<=x1) return true;
	if(x<=y1&&y1<=x1) return true;
	return false;
}
int main(){
	cin>>n>>f;
	cin>>s;
	if(f>=(n/3)+1){
		cout<<0;
		return 0;
	}
	for(int i=0;i<n-2;i++){
		string s1=s.substr(i,3);
		if(s1[0]!=s1[1]&&s1[1]==s1[2]){
			if(mp[s1]==0){
				cnt1++;
				mp1[cnt1]=s1;
			}
			mp[s1]++;
			vis[mp[s1]][s1]=i;
		}
	}
	for(int i=1;i<=cnt1;i++){
		if(mp[mp1[i]]>=f){
			cnt++;
			ans[cnt]=mp1[i]; 
			vis1[mp1[i]]=1;
		}
	}
	for(int i=1;i<=cnt1;i++){
		for(int j=0;j<n-2;j++){
			short flag=0;
			string s1=s.substr(j,3);
			if(check(s1,mp1[i])==true){
				for(int k=1;k<=mp[mp1[i]];k++){
					if(pos(vis[k][mp1[i]],j)) flag=1;
				}
				if(flag==0&&mp[mp1[i]]>=f-1&&vis1[mp1[i]]!=1){
					cnt++;
					ans[cnt]=mp1[i];
					vis1[mp1[i]]=1;
					break;
				}
			}
		}
	}
  //特判
	if(s[0]==s[1]&&s[1]==s[2]){
		cout<<25<<'\n';
		char c1=s[0];
		for(char c='a';c<='z';c++){
			if(c1==c) c++;
			cout<<c<<s[1]<<s[2]<<'\n';
		}
		return 0;	
	}
	sort(ans+1,ans+1+cnt);
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++){
		cout<<ans[i]<<'\n';
	}
} 
```

---

## 作者：ARIS1_0 (赞：3)

题解区好多都是暴力枚举字符然后判合法的啊。

这是一篇暴力枚举原串中所有可能的子串的题解。

## 思路

用 `map` 统计所有可能的子串，把答案存进 `set` 里面，这样既不用手动排序也不用手动去重。

我们先把所有的 $\texttt{MOO}$ 式子串全部丢进 `map` 里面统计数量，然后分类讨论：

1. 若出现次数 $\ge F$，直接加入 `set` 中。

2. 若出现次数 $= F-1$，那么进入原字符串中去寻找一个可以被修改成为 $\texttt{MOO}$ 式子串的子串，若能找到，则加入 `set`，否则跳过。

3. 若出现次数 $<F-1$，跳过。

那么重点如何去寻找可以被修改成为 $\texttt{MOO}$ 式子串的子串：

首先，在原串中把所有的原 $\texttt{MOO}$ 式子串全部进行标记，修改一定不能在这些串上面进行。随后在剩下的没有标记的子串中寻找 $\texttt{?OO}$ 或 $\texttt{M?O}$ 或 $\texttt{MO?}$ 式子串即可。找到任意一个，则该 $\texttt{MOO}$ 式子串合法。

当然，发现当 $F=1$ 时，任意子串都能进行修改，我们进行以下讨论：

1. $\texttt{?OO}$ 式子串：枚举开头字符，注意不能形成 $\texttt{OOO}$ 式子串。

2. $\texttt{M?O}$ 式子串：修改为 $\texttt{MOO}$ 式子串或 $\texttt{M??}$ 式子串即可。

3. $\texttt{OO?}$ 式子串或 $\texttt{O?O}$ 式子串：怎么修改都不合法，跳过。

关于 `map` 的遍历：用 `iterator` 进行遍历，注意此时的 `iterator` 为类似 `pair` 类型的指针：

- `it->first` 指向键值，即下标。

- `it->second` 指向对应的映射。

接受该指针可用 ```pair<键值类型,映射类型>P=*it;```。

遍历 `map` 时间复杂度为 $O(n\log n)$。

整个程序的复杂度为 $O(n^2\log n)$，但是因为有前面的分讨，完全是跑不满的，甚至还能挤进最优解第一页。

```cpp
//程序开头已省略
//已格式化，加强了可读性
string s, v;
int n, k;
set<string>anss;
map<string, int>mp;
map<string, int>::iterator it;
int main() {
    n = read();
    k = read();
    cin >> s;
    v = s;

    for (int i = 0; i < n - 2; i++) {
        string tmp;

        if (s[i] != s[i + 1] && s[i + 1] == s[i + 2]) {
            tmp.clear();
            tmp += s[i];
            tmp += s[i + 1];
            tmp += s[i + 2];
            mp[tmp]++;

            if (mp[tmp] >= k)
                anss.insert(tmp);
        }
    }

    for (it = mp.begin(); it != mp.end(); it++) {
        string t = it->first;
        int num = it->second;

        if (num != k - 1)
            continue;

        v = s;

        for (int i = 0; i < n - 2; i++) {
            if (s[i] == t[0] && s[i + 1] == t[1] && s[i + 2] == t[2]) {
                v[i] = v[i + 1] = v[i + 2] = '#';
            }
        }

        for (int i = 0; i < n - 2; i++) {
            if (s[i] == t[0] && s[i + 1] == t[1] && s[i + 2] != t[2] && v[i] != '#' && v[i + 2] != '#' && v[i + 1] != '#')
                anss.insert(t);
            else if (s[i] == t[0] && s[i + 1] != t[1] && s[i + 2] == t[2] && v[i] != '#' && v[i + 2] != '#' &&
                     v[i + 1] != '#')
                anss.insert(t);
            else if (s[i] != t[0] && s[i + 1] == t[1] && s[i + 2] == t[2] && v[i] != '#' && v[i + 2] != '#' &&
                     v[i + 1] != '#')
                anss.insert(t);
        }
    }

    if (k == 1) {
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == s[i])
                        continue;

                    string tmp;
                    tmp += c;
                    tmp += s[i];
                    tmp += s[i];
                    anss.insert(tmp);
                }
            }
        }
    }

    if (k == 1) {
        for (int i = 0; i < n - 2; i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == s[i] || (c != s[i + 1] && c != s[i + 2]))
                    continue;

                string tmp;
                tmp += s[i];

                if (c == s[i + 2]) {
                    tmp += c;
                    tmp += s[i + 2];
                    anss.insert(tmp);
                } else {
                    tmp += s[i + 1];
                    tmp += c;
                    anss.insert(tmp);
                }

            }
        }
    }

    cout << anss.size() << "\n";

    for (auto i : anss)
        cout << i << "\n";

    return 0;
}
```

---

## 作者：YBJ1006 (赞：2)

直接暴力枚举每一种哞哞叫，记哞哞叫出现次数为 $cnt$ 
那么分为三种情况。

1. `cnt>=F`  那么这个哞哞叫一定为答案。
2. `cnt==F-1` 那么需检查一遍未使用过的字符串，通过修改一个字符，可以使字符串为哞哞叫，那么这个哞哞叫也为答案。
3. `cnt<F-1` 显然通过修改一个字符是满足不了的，所以不可能为答案。

具体细节见代码

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
const int N = 20000 + 20;
char a[N];
string s[700];
int tot,vis[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, f;
    cin >> n >> f;
    cin >> a + 1;
    for (char i = 'a'; i <= 'z'; i++)
    {
        for (char j = 'a'; j <= 'z'; j++)
        {
            if (i == j)
                continue;
            int cnt = 0;
            memset(vis, 0, sizeof(vis));
            for (int id = 1; id <= n - 2; id++)
            {
                if (a[id] == i && a[id + 1] == j && a[id + 2] == j)
                {
                    vis[id] = 1, vis[id + 1] = 1, vis[id + 2] = 1;
                    cnt++;
                }
            }
            if (cnt >= f)
            {
                s[++tot] += i;
                s[tot] += j;s[tot]+=j;
            }
            else if (cnt == f - 1)
            {
                for (int id = 1; id <= n-2; id++)
                {
                    if (a[id] == i && a[id + 1] == j && vis[id + 2] == 0)
                    {
                        s[++tot] += i;
                        s[tot] += j; s[tot] += j;
                        break;
                    }
                    if (a[id + 2] == j && a[id + 1] == j && vis[id] == 0)
                    {
                        s[++tot] += i;
                        s[tot] += j; s[tot] += j;
                        break;
                    }
                    if (a[id] == i && a[id + 2] == j && vis[id + 1] == 0)
                    {
                        s[++tot] += i;
                        s[tot] += j; s[tot] += j;
                        break;
                    }
                }
            }
        }
    }
    cout << tot << '\n';
    for (int i = 1; i <= tot; i++)
    {
        cout << s[i] << '\n';
    }
    return 0;
}
```

---

## 作者：__yrq__ (赞：2)

## 思路：
$O(n)$ 暴力。

双重循环分别枚举 $c_i$ 和 $c_j$，然后在字符串中找包含了多少个子串 $c_ic_jc_j$。

因为题目中说输入的字符串中可能存在一个字符与原文不同，也就是可以修改任意一个字符，那么就可以再找一下有没有通过修改一个字符就能变成子串 $c_ic_jc_j$ 的。

注意不可以修改那些已经是 $c_ic_jc_j$ 的子串里的字符，不然和之前不修改的子串数是一样的，没有变化。

最后判断一下子串 $c_ic_jc_j$ 出现的次数是否大于 $F$ 次就好啦！
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,s1[200005];
bool vis[20005];
int n,f,a[30][30],m=0,b[30][30];
int main()
{
	cin>>n>>f>>s;
	for(int i=0;i<26;i++)
		for(int j=0;j<26;j++)
		{
			if(i==j) continue;
			memset(vis,0,sizeof(vis));
			int t=0,t1=0;
			for(int k=1;k<n-1;k++)
			{
				if(s[k-1]==char(i+'a')&&s[k]==s[k+1]&&s[k]==char(j+'a'))
				{
					t++;
					vis[k-1]=vis[k]=vis[k+1]=1;
				}
			}
			for(int k=1;k<n-1;k++)
			{
				if(s[k]==s[k+1]&&s[k]==char(j+'a'))
				{
					if(s[k-1]!=char(i+'a')&&vis[k-1]==0) t1=1;
				}
				else if(s[k-1]==char(i+'a'))
				{
					if(s[k]==char(j+'a')&&vis[k+1]==0) t1=1;
					if(s[k+1]==char(j+'a')&&vis[k]==0) t1=1;
				}
			}
			if(t+t1>=f)
			{
				s1[++m]+=char(i+'a');
				s1[m]+=char(j+'a');
				s1[m]+=char(j+'a');
			}
		}
	cout<<m<<endl;
	sort(s1+1,s1+m+1);
	for(int i=1;i<=m;i++) cout<<s1[i]<<endl;
	return 0;
}
```

---

## 作者：zhangzirui66 (赞：2)

有点暴力的模拟做法。

观察到 `moo` 形式的字符串只会有 $2$ 种字符，我们进行暴力枚举。

枚举 `moo` 叫的位置，分两种情况分讨：

- 理想情况，无损坏，判断即可，并记录此处已有 `moo` 叫。
- 坏掉了，由于只坏了一个，使用变量记录是否修复过，若没有，检查是否可修。

时间复杂度显然为 $O(|s|^2n)$，时限 $2$ 秒，较为可行。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, v[20005], cnt;
string s, ans[20005];
map<string, int> mp;
int main(){
	cin >> n >> m >> s;
	for(char a = 'a'; a <= 'z'; a ++)
		for(char b = 'a'; b <= 'z'; b ++){
			if(a == b) continue;
			string m1, m2; m1 = a, m2 = b;
			int t = 0, sum = 0;
			for(int i = 0; i < n - 2; i ++) v[i] = 0;
			for(int i = 0; i < n - 2; i ++){
				string x, y, z; x = s[i], y = s[i + 1], z = s[i + 2];
				if(m1 + m2 + m2 == x + y + z){
					v[i] = v[i + 1] = v[i + 2] = 1;
					sum ++, i += 2;
				}
			}
			for(int i = 0; i < n - 2; i ++){
				if(!v[i] && !v[i + 1] && !v[i + 2]){
					string x, y, z; x = s[i], y = s[i + 1], z = s[i + 2];
					if(!t && (m1 + m2 + m2 == m1 + y + z || m1 + m2 + m2 == x + m2 + z || m1 + m2 + m2 == x + y + m2)){
						sum ++, t = 1, i += 2;
					}
				}
			}
			if(sum >= m) ans[++ cnt] = m1 + m2 + m2;
		}
	cout << cnt << "\n";
	for(int i = 1; i <= cnt; i ++) cout << ans[i] << "\n";
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

另类思路：判断每一个字符串是否可行。

于是，我们可以选择使用动态规划。两维，第一维是到哪个位置，第二位是有没有改。方程很简单，看代码就行了。

具体的，我们维护一个二维的数组 $dp_{i,0/1}$，表示在 $i$ 位置，（不）修改的情况下的最大匹配数量。

当 $[i-2,i]$ 区间可以直接匹配对应的字符串的时候，$dp_{i,j}=\max(dp_{i-1,j},dp_{i-3,j}+1)$，而当我们可以通过只修改一个字符达到目的的时候，$dp_{i,1}=\max(dp_{i-1,1},dp_{i-3,0}+1)$。如果都不行，则 $dp_{i,j}=dp_{i-1,j}$。

这样，复杂度为 $O(n)$，带 $26^2$ 的常数可以通过。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[200005][2], n, m, mx[200005][2];
char s[200005]; vector<pair<int,int>>moo;
inline int get(int x, int y) {
	for (int i = 3; i <= n; ++i) {
		int s1 = s[i - 2] == x, s2 = s[i - 1] == y, s3 = s[i] == y;
		dp[i][0] = mx[i - 3][0] + (s1 && s2 && s3);
		dp[i][1] = mx[i - 3][1] + (s1 && s2 && s3);
		dp[i][1] = max(dp[i][1], mx[i - 3][0] + (s1 + s2 + s3 >= 2));
		mx[i][1] = max(mx[i - 1][1], dp[i][1]);
		mx[i][0] = max(mx[i - 1][0], dp[i][0]);
	}
	return mx[n][1];
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> (s + 1);
	for (int i = 1; i <= n; ++i)
		s[i] = s[i] - 'a' + 1;
	for (int i = 1; i <= 26; ++i)
		for (int j = 1; j <= 26; ++j)
			if (i != j&&get(i,j)>=m)
				moo.emplace_back(make_pair(i, j));
	cout << moo.size() << endl;
	for (pair<int, int>& p : moo)
		putchar(p.first + 'a' - 1),
		putchar(p.second + 'a' - 1),
		putchar(p.second + 'a' - 1),
		putchar('\n');
}
/*
hack:
8 2
baacaacc
*/
```

---

## 作者：vanueber (赞：2)

# 题目大意

问所有形似 $c_ic_jc_j(c_i \not = c_j)$ 的字串，满足条件：能够通过改变原串中的一个字符，使它的出现次数大于等于 $f$。

# 题目分析

思路还是很显然的，考虑枚举 $c_i,c_j$，验证这样的字串是否满足条件。

如果不考虑改变的字符，先在原串中扫一遍，求出当前出现的次数，并将这些位置打上标记。

如果出现次数大于等于 $f$，一定可以满足条件，加入答案。

如果等于 $f-1$ ，再扫一遍，此时应满足的条件是：
$$
[ss_i=c_i]+[ss_{i+1}=c_j]+[ss_{i+2}=c_j]=2
$$
且位置 $i,i+1,i+2$ 均未被标记。

如果出现次数小于 $f-1$，一定不可以作为答案。

# 代码实现


```cpp
#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

inline int read()
{
	int w = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		w = (w << 1) + (w << 3) + (ch ^ 48);
		ch = getchar();
	}
	return w * f;
}

inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
const int maxn=200005;
int n,f;
string ss;
vector<string> ans;
bool vis[maxn];

int main()
{
	n=read(),f=read();
	cin>>ss;

	for(char c1='a';c1<='z';++c1)
	{
		for(char c2='a';c2<='z';++c2)
		{
			//考虑c1c2c2最多出现几次
			memset(vis,0,sizeof vis);
			if(c1==c2) continue;
			string tar="   ";
			tar[0]=c1,tar[1]=c2,tar[2]=c2;
			int cnt=0;
			for(unsigned int i=0;i<ss.size();++i)
			{
				int tot=(ss[i]==tar[0])+(ss[i+1]==tar[1])+(ss[i+2]==tar[2]);
				if(tot==3)
				{
					vis[i]=vis[i+1]=vis[i+2]=1;
					++cnt;
					i=i+2;
					continue;
				}
			}
			if(cnt>=f) ans.push_back(tar);
			if(cnt<f-1) continue;
			for(int i=0;i<ss.size();++i)
			{
				int tot=(ss[i]==tar[0])+(ss[i+1]==tar[1])+(ss[i+2]==tar[2]);
				if(tot==2)
				{
					int vis_tot=vis[i]+vis[i+1]+vis[i+2];
					if(vis_tot==0) ans.push_back(tar);
				}
			}
		}
	}
	sort(ans.begin(),ans.end());
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	cout<<ans.size()<<endl;
	for(string &s:ans)
	{
		cout<<s<<endl;
	}
	return 0;
}


```

---

## 作者：Statax (赞：1)

## 前言

其实感觉也只有橙。

## 分析

暴力枚举每种叫声，然后线性检查。

注意检查的时候先匹配可以直接配的，再考虑坏掉字符的匹配，这两步不能同时进行。

然后就做完了。

## 代码

我的代码都挺长的，时间复杂度 $O(n\times|\Sigma|^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) x & (-x)

using namespace std;
constexpr int MAXN = 1e6 + 5;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;

int n, f, res;
bool isSpare[MAXN];
string str, ans[MAXN];

bool compar(string a, string b)
{
    bool fg = false;
    for (int i = 0; i < 3; ++i) {
        if (a[i] != b[i]) {
            if (fg)
                return false;
            fg = true;
        }
    }
    return true;
}

void work(string comp)
{
    memset(isSpare, false, sizeof isSpare);
    int cnt = 0;
    for (int idx = 0; idx + 2 < n; ++idx) {
        if (str.substr(idx, 3) == comp) {
            ++cnt, idx += 2;
            isSpare[idx] = isSpare[idx - 1] = isSpare[idx - 2] = true;
        }
    }
    for (int idx = 0; idx + 2 < n; ++idx) {
        if (isSpare[idx]) {
            idx += 2;
            continue;
        }
        if (!isSpare[idx + 1] && !isSpare[idx + 2] && compar(str.substr(idx, 3), comp)) {
            ++cnt;
            break;
        }
    }
    if (cnt >= f)
        ans[++res] = comp;
}

signed main()
{
    cin >> n >> f >> str;
    for (int i = 0; i <= 25; ++i) {
        for (int j = 0; j <= 25; ++j) {
            if (i == j)
                continue;
            string comp = "aaa";
            comp[0] += i, comp[1] += j, comp[2] += j;
            work(comp);
        }
    }
    cout << res << endl;
    for (int i = 1; i <= res; ++i)
        cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：SSqwq_ (赞：0)

## 分析

要求求出修改任意一个字符后能够出现超过 $k$ 次的 ABB 式字符串的并集。

拆出修改每一位并枚举所有可能性，计算相邻字符的贡献即可。

代码细节实现有一定挑战性。

时间复杂度 $O(m^2n)$，其中 $m$ 是字符集大小，本题 $m=26$。足以通过此题。

## Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,ans,a[20001],b[28][28],c[28][28];
string s;
void work(){
	cin>>n>>k>>s;
	s=" "+s;
	for(int i=1;i<=n;++i){
		a[i]=s[i]-'a'+1;
	}
	for(int i=1;i+2<=n;++i){
		if(a[i+1]==a[i+2]&&a[i]!=a[i+1]){
			b[a[i]][a[i+1]]++;
			if(b[a[i]][a[i+1]]>=k&&!c[a[i]][a[i+1]]){
				c[a[i]][a[i+1]]=1;
				ans++;
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=26;++j){
			if(i<=n-2){
				if(a[i+1]==a[i+2]&&a[i]!=a[i+1]){
					b[a[i]][a[i+1]]--;
				}
			}
			if(i>=2&&i<=n-1){
				if(a[i+1]==a[i]&&a[i-1]!=a[i]){
					b[a[i-1]][a[i]]--;
				}
			}
			if(i>=3){
				if(a[i-1]==a[i]&&a[i]!=a[i-2]){
					b[a[i-2]][a[i]]--;
				}
			}
			if(i<=n-2){
				if(j!=a[i+1]&&a[i+1]==a[i+2]){
					b[j][a[i+1]]++;
					if(b[j][a[i+1]]>=k&&!c[j][a[i+1]]){
						c[j][a[i+1]]=1;
						ans++;
					}
				}
			}
			if(i>=2&&i<=n-1){
				if(a[i-1]!=j&&j==a[i+1]){
					b[a[i-1]][j]++;
					if(b[a[i-1]][j]>=k&&!c[a[i-1]][j]){
						c[a[i-1]][j]=1;
						ans++;
					}
				}
			}
			if(i>=3){
				if(a[i-2]!=j&&j==a[i-1]){
					b[a[i-2]][j]++;
					if(b[a[i-2]][j]>=k&&!c[a[i-2]][j]){
						c[a[i-2]][j]=1;
						ans++;
					}
				}
			}
			if(i<=n-2){
				if(j!=a[i+1]&&a[i+1]==a[i+2])b[j][a[i+1]]--;
			}
			if(i>=2&&i<=n-1){
				if(a[i-1]!=j&&j==a[i+1])b[a[i-1]][j]--;
			}
			if(i>=3){
				if(a[i-2]!=j&&j==a[i-1])b[a[i-2]][j]--;
			}
			if(i<=n-2){
				if(a[i+1]==a[i+2]&&a[i]!=a[i+1]){
					b[a[i]][a[i+1]]++;
				}
			}
			if(i>=2&&i<=n-1){
				if(a[i+1]==a[i]&&a[i-1]!=a[i]){
					b[a[i-1]][a[i]]++;
				}
			}
			if(i>=3){
				if(a[i-1]==a[i]&&a[i]!=a[i-2]){
					b[a[i-2]][a[i]]++;
				}
			}
		}
	}
	cout<<ans<<"\n";
	for(int i=1;i<=27;++i){
		for(int j=1;j<=27;++j){
			if(c[i][j]){
				cout<<(char)(i-1+'a')<<(char)(j-1+'a')<<(char)(j-1+'a')<<"\n";
			}
		}
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：signed_long_long (赞：0)

好臭啊哼哼啊啊……

# 题目解法

考虑贪心。

下面的 `a` 和 `b` 不是字符 `a` 和 `b`，是任意两个互不相同的小写字母。

由于小写字母只有 $26$ 个，所以可以枚举两个字母作为 `abb` 形式的 `a` 和 `b`，再枚举一遍字符串，对于相邻三个字符：

- 为 `abb` 形式：直接把答案增加 $1$ 即可。
- 为 `ab?` 形式：
  
   -  接下来两个的字符若为 `bb` 且 `?` 为 `a`：不改了，因为改了也没用。
   -  否则，改一下。
- 为 `aab` 形式：

  - 接下来的一个字符为 `b`：不改了，改了也没用。
  - 否则，改一下。
- 为 `?bb`：直接改掉。

如果答案大于 $F$，那么保存答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f;
string s;
int cnt=0;
string answ[50000];
int main(){
	cin>>n>>f;
	cin>>s;
	s=' '+s;
	s=s+' ';
	s=s+' ';
	for(char a='a';a<='z';a++){
		for(char b='a';b<='z';b++){
			if(a==b) continue;
			int ans=0;
			bool use=false;
			for(int i=1;i<=n-2;i++){
				if(s[i]==a and s[i+1]==s[i+2] and s[i+1]==b){
					ans++;
					i+=2;
				}else if(s[i]==a and s[i+1]==b){
					if(s[i+2]==a and s[i+3]==b and s[i+4]==b){
						;
					}else if(!use){
						ans++;
						use=true;
					}
				}else if(s[i]==a and s[i+1]==a and s[i+2]==b){
					if(s[i+3]==b){
						;
					}else if(!use){
						ans++;
						use=true;
					}
				}else if(s[i+1]==b and s[i+2]==b){
					if(!use){
						ans++;
						use=true;
					}
				}
			}
			if(ans>=f){
				answ[++cnt]+=a;
				answ[cnt]+=b;
				answ[cnt]+=b;
			}
		}
	} 
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		cout<<answ[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：ChenZQ (赞：0)

首先，一个哞叫是由两种字符构成的，我们可以枚举这两种字符。

然后枚举整个字符串，先统计原本有多少个存在的哞叫，然后在看相邻三个，如果能通过一次变换就把这相邻三个变得和枚举的哞叫一样，就把他们加入答案。最后看他的次数是否大于等于 $F$ 就行。

时间复杂度就是 $O(n)$，计算量差不多就再乘上 $26$ 的平方，不会超时。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,F,ans;string s;

string v[100010];
int ff[200010];

int main()
{
	scanf("%d%d",&n,&F);
	cin>>s;
	//asdfasdfasdfad
	for(char i='a';i<='z';i++)
	{
		for(char j='a';j<='z';j++)
		{
			memset(ff,0,sizeof(ff));
			string gg;
			gg+=i;gg+=j;gg+=j;
			int cnt=0;
			if(i==j)continue;
			for(int u=0;u<s.size()-2;u++)
			{/*kkk*/
				if(ff[u]||ff[u+1]||ff[u+2]) continue;
				string p;
				p+=s[u];
				p+=s[u+1];
				p+=s[u+2];
				int ret=0;
				for(int k=0;k<3;k++)
				{
					if(p[k]!=gg[k]) ret++;
				}
				if(!ret)
				{
					cnt++;
					ff[u]=1;
					ff[u+1]=1;
					ff[u+2]=1;
				}
				
			}
			for(int u=0;u<s.size()-2;u++)
			{
				/*bb*/
				if(ff[u]||ff[u+1]||ff[u+2]) continue;
				string p;
				p+=s[u];
				p+=s[u+1];
				p+=s[u+2];
				int ret=0;
				for(int k=0;k<3;k++)
				{
					if(p[k]!=gg[k]) ret++;
				}
				if(ret==1)
				{
					cnt++;
					ff[u]=1;
					ff[u+1]=1;
					ff[u+2]=1;
					break;
				}
			}
			if(cnt>=F)
			{
				string t1,t2;
				t1=i;t2=j;
				v[++ans]=t1+t2+t2;
			}
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)cout<<v[i]<<endl;
}
```

---

## 作者：K_yuxiang_rose (赞：0)

因为英文字母十分有限，所以我们只要枚举可能出现的组合再判断是否可行即可，时间复杂度 $O(26^2N)$，忽略常数为 $O(N)$。

判断时贪心，如果能更换字符使得满足条件，并且对前面满足条件的串没有影响，就用掉更换字符，最后统计出现次数是否大于等于 $F$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[30][30];
int b[20005];//用来查询这一位是否被用上了
signed main()
{
	int n,f;
	cin>>n>>f;
	string s;
	cin>>s;
	int ans=0;
	for(int x=0;x<26;x++)
	{
		for(int y=0;y<26;y++)
		{
			for(int i=0;i<n;i++) b[i]=0;
			if(x==y) continue;
			int cnt=0,flag=1;
			for(int i=0;i<n-2;i++)
			{
				if(s[i]==char('a'+x)&&s[i+1]==char('a'+y)&&s[i+1]==s[i+2])
				{
					cnt++;
					b[i]=b[i+1]=b[i+2]=1;
					i+=2;
					continue;
				}
			}
			for(int i=0;i<n-2;i++)
			{
				if(s[i+1]==s[i+2]&&s[i+1]==char('a'+y)&&flag&&!b[i]&&!b[i+1]&&!b[i+2])
				{
					flag=0;
					cnt++;
					i+=2;
					continue;
				}
				if(s[i]==char('a'+x)&&(s[i+1]==char('a'+y)||s[i+2]==char('a'+y))&&flag&&!b[i]&&!b[i+1]&&!b[i+2])
				{
					flag=0;
					cnt++;
					i+=2;
					continue;
				}
			}
			if(cnt>=f)
			{
				ans++;
				a[x][y]=1;
			}
		}
	}
	cout<<ans<<endl;
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			if(a[i][j])
			{
				cout<<char('a'+i)<<char('a'+j)<<char('a'+j)<<endl;
			}
		}
	}
	return 0;
} 

```

---

## 作者：Your_Name (赞：0)

## 题解
可以发现我们每次最多改一个，我们设为 $i$，那么被这个地方影响的（即会因为这个改了而凑不出形如 $abb$）有 $[i - 2,i-1,i],[i-1,i,i+1],[i,i+1,i+2]$ 三个地方。

那么我们就可以直接把原字符串扫一遍，把每个合法串的贡献加上，然后丢到 set 里，每次改的时候动态删，加贡献即可，如果满足数量限制就丢到 set 里，最后输出即可。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
map<string, int> cnt;
string s;
int n, f;
set<string> ss;
void del(int i){
	if(s[i] != s[i + 1] && s[i + 1] == s[i + 2]){
		string k = "";
		k += s[i];
		k += s[i + 1];
		cnt[k] --;
	}
}//删
void add(int i){
	if(s[i] != s[i + 1] && s[i + 1] == s[i + 2]){
		string k = "";
		k += s[i];
		k += s[i + 1];
		//cout << k << '\n';
		cnt[k] ++;
		if(cnt[k] >= f){
			k += s[i + 1];
			ss.insert(k);
		}
	}
}//加
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> f >> s;
	for(int i = 0; i < n - 2; i ++)add(i);//原串的贡献
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < 26; j ++){
			if((char)(j + 'a') == s[i]){
				continue;
			}//不写也行，反正 set 会去重
			if(i >= 2)del(i - 2);
			if(i >= 1 && i < n - 1)del(i - 1);
			if(i < n - 2)del(i);
			char c = s[i];
			s[i] = char(j + 'a');
			if(i >= 2)add(i - 2);
			if(i >= 1 && i < n - 1)add(i - 1);
			if(i < n - 2)add(i);
			if(i >= 2)del(i - 2);
			if(i >= 1 && i < n - 1)del(i - 1);
			if(i < n - 2)del(i);
			s[i] = c;//复原
			if(i >= 2)add(i - 2);
			if(i >= 1 && i < n - 1)add(i - 1);
			if(i < n - 2)add(i);//小心越界
		}
	}
	cout << ss.size() << '\n';
	for(auto i : ss){
		cout << i << '\n';
	}
	return 0;
}
```
_完结撒花。_

---

## 作者：Su777 (赞：0)

# USACO 24Dec Bronze C 题解

## 题意

定义一个长度为 $3$ 的字符串 $s$ 为“牛牛字符串”，当且仅当 $s_0\neq s_1$ 且 $s_1=s_2$。

给定一个长为 $n$ 的字符串，和一个参数 $f$。定义一种“牛牛”字符串是“好的”，当且仅当可以通过对字符串中的**最多** $1$ 个字符进行修改，使得字符串中这种“牛牛字符串”的数量达到 $f$。按照字典序从小到大输出所有的“好的”“牛牛字符串”。

## 暴力

$O(n)$ 枚举不修改和修改一个字符可能产生的所有字符串，然后用 `map` 寻找出现次数大于等于 $f$ 的“牛牛字符串”。但此做法常数过大。

```cpp
for (int a = 0; a < n; a ++) {
    char ori = s[a];
    for (char b = 'a'; b <= 'z'; b ++) {
        s[a] = b;
        mp.clear();
        for (int i = 0; i + 2 < n; i ++) {
            string t = s.substr(i, 3);
            if (t[0] != t[1] && t[1] == t[2]) {
                // cout << t << "\n";
                mp[t] ++;
            }
        }
        for (auto it: mp) {
            if (it.second >= f) {
                ans.push_back(it.first);
            }
        }            
    }
    s[a] = ori;
}
sort(ans.begin(), ans.end());
ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
cout << ans.size() << "\n";
for (auto s: ans) {
    cout << s << "\n";
}
```

## 正解

不难发现，对于一个“牛牛字符串”，如果它想要成为一个答案，只有两种方式：

1.  一开始就在字符串中出现超过 $f$ 次。
2.  一开始在字符串中出现了 $f-1$ 次，然后通过修改一个字符使得它多出现了 $1$ 次，即出现了 $f$ 次。

第一种字符串很好判断，$O(n)$ 遍历加上一个 `map` 遍历即可。

然后开始处理第二种字符串。我的做法是，$O(n)$ 遍历 `map` 中的所有“牛牛字符串”。对于每一种字符串，先在这种字符串在原串中出现的位置打上标记，因为如果修改这些位置，一定是不优的（因为破坏了原有的“牛牛字符串”）。在另外的位置中，找到与该“牛牛字符串”匹配数达到 $2$ 的字符串，然后修改剩下的一个字符，就可以达到目的。

> 注意 $f=1$ 时，$f-1=0$，只能用暴力方法去做。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n, f;
bool vis[200005];
string s;
map<string, ll> mp;
vector<string> ans;

int main() {
    // freopen("C.in", "r", stdin);
    // freopen("C.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> f >> s;
    if (f == 1) {
        for (int a = 0; a < n; a ++) {
            char ori = s[a];
            for (char b = 'a'; b <= 'z'; b ++) {
                s[a] = b;
                mp.clear();
                for (int i = 0; i + 2 < n; i ++) {
                    string t = s.substr(i, 3);
                    if (t[0] != t[1] && t[1] == t[2]) {
                        // cout << t << "\n";
                        mp[t] ++;
                    }
                }
                for (auto it: mp) {
                    if (it.second >= f) {
                        ans.push_back(it.first);
                    }
                }            
            }
            s[a] = ori;
        }
        sort(ans.begin(), ans.end());
        ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
        cout << ans.size() << "\n";
        for (auto s: ans) {
            cout << s << "\n";
        }
        return 0;
    }
    for (int i = 0; i + 2 < n; i ++) {
        string t = s.substr(i, 3);
        if (t[0] != t[1] && t[1] == t[2]) {
            // cout << t << "\n";
            mp[t] ++;
        }
    }
    for (auto it: mp) {
        // cout << it.first << " " << it.second << "\n";
        if (it.second >= f) {
            ans.push_back(it.first);
            continue;
        }
        if (it.second < f - 1) {
            continue;
        }
        // it.second == f - 1
        for (int i = 0; i < n; i ++) vis[i] = 0;
        for (int i = 0; i + 2 < n; i ++) {
            string t = s.substr(i, 3);
            if (t == it.first) {
                vis[i] = vis[i+1] = vis[i+2] = 1;
            }
        }
        bool ok = false;
        for (int i = 0; i + 2 < n; i ++) {
            string t = s.substr(i, 3);
            if (t[0] == it.first[0] && t[1] == it.first[1]
            || t[0] == it.first[0] && t[2] == it.first[2]
            || t[1] == it.first[1] && t[2] == it.first[2]) {
                if (!vis[i] && !vis[i+1] && !vis[i+2]) {
                    ok = true; break;
                }
            }
        }
        if (ok) ans.push_back(it.first);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto it: ans) cout << it << "\n";
    return 0;
}
```

---

## 作者：shinzanmono (赞：0)

枚举每种叫声，然后设 $dp_{i,0/1}$ 表示整个字符串，匹配到了 $i$，改了 $0/1$ 个的最大出现次数。考虑当前字符结尾的子串是否需要选中，不需要直接继承 $f_{i,j}$，否则考虑这个子串要改 $k$ 个位置，然后 $f_{i,j}=\max f_{i-3,j-k}+1$。


没啥难度，代码不放了，时间复杂度 $O(n|\Sigma|^2)$。

---

