# Matching Names

## 题目描述

Teachers of one programming summer school decided to make a surprise for the students by giving them names in the style of the "Hobbit" movie. Each student must get a pseudonym maximally similar to his own name. The pseudonym must be a name of some character of the popular saga and now the teachers are busy matching pseudonyms to student names.

There are $ n $ students in a summer school. Teachers chose exactly $ n $ pseudonyms for them. Each student must get exactly one pseudonym corresponding to him. Let us determine the relevance of a pseudonym $ b $ to a student with name $ a $ as the length of the largest common prefix $ a $ and $ b $ . We will represent such value as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF566A/49184e0d721201acb7ec1d32721635b1fa5d0628.png). Then we can determine the quality of matching of the pseudonyms to students as a sum of relevances of all pseudonyms to the corresponding students.

Find the matching between students and pseudonyms with the maximum quality.

## 说明/提示

The first test from the statement the match looks as follows:

- bill $ → $ bilbo (lcp = 3)
- galya $ → $ galadriel (lcp = 3)
- gennady $ → $ gendalf (lcp = 3)
- toshik $ → $ torin (lcp = 2)
- boris $ → $ smaug (lcp = 0)

## 样例 #1

### 输入

```
5
gennady
galya
boris
bill
toshik
bilbo
torin
gendalf
smaug
galadriel
```

### 输出

```
11
4 1
2 5
1 3
5 2
3 4
```

# 题解

## 作者：skylee (赞：2)

# [CF566A]Matching Names
## 题目大意：
A组和B组各$n(n\le10^5)$个字符串$(\sum|S|\le8\times10^5)$，将它们两两匹配，使得每组两个字符串的LCP之和最大，输出最大值，并输出方案。

## 思路：
Trie上贪心，在深的结点能匹配则匹配。

## 源代码：
```cpp
#include<set>
#include<cstdio>
#include<vector>
const int N=1e5+1,L=8e5+1;
int n,ans;
char s[L];
std::vector<std::pair<int,int> > v;
class Trie {
	private:
		std::set<int> set[L][2];
		int ch[L][26],par[L],sz;
		int idx(const char &c) const {
			return c-'a';
		}
		void erase(int p,const int &x,const bool &t) {
			while(p) {
				set[p][t].erase(x);
				p=par[p];
			}
			set[0][t].erase(x);
		}
	public:
		void insert(char s[],const int &id,const bool &t) {
			set[0][t].insert(id);
			for(register int i=0,p=0;s[i];i++) {
				const int c=idx(s[i]);
				if(!ch[p][c]) {
					ch[p][c]=++sz;
					par[ch[p][c]]=p;
				}
				p=ch[p][c];
				set[p][t].insert(id);
			}
		}
		void solve(const int &p,const int &dep) {
			for(register int i=0;i<26;i++) {
				if(ch[p][i]) {
					solve(ch[p][i],dep+1);
				}
			}
			while(!set[p][0].empty()&&!set[p][1].empty()) {
				ans+=dep;
				const int x=*set[p][0].begin();
				const int y=*set[p][1].begin();
				v.push_back(std::make_pair(x,y));
				erase(p,x,0);
				erase(p,y,1);
			}
		}
};
Trie t;
int main() {
	scanf("%d",&n);
	for(register int i=1;i<=n;i++) {
		scanf("%s",s);
		t.insert(s,i,0);
	}
	for(register int i=1;i<=n;i++) {
		scanf("%s",s);
		t.insert(s,i,1);
	}
	t.solve(0,0);
	printf("%d\n",ans);
	for(register unsigned i=0;i<v.size();i++) {
		printf("%d %d\n",v[i].first,v[i].second);
	}
	return 0;
}
```

---

## 作者：qfpjm (赞：0)

# 题解

- 看到公共前缀，我们就会想到 `trie`。这题要求最大的公共前缀和，那么我们可以考虑贪心。

- 我们对于每个前缀，在 `trie` 上能走多深就多深，每次用公共前缀最长的一个学生和一个笔名匹配。因为要求前缀长度的和最大，所以当前最大肯定是最优的，如有当前不选，那么在未来不可能找到更有的与该学生匹配的笔名。

- 实现的话比较简单，讲学生名字和笔名存到同一颗 `trie` 中，用 $0,1$ 区别。每次递归顺着前缀往下记录最深的可匹配的两个，用数组存下即可。

# 代码

- 上面讲的也比较清楚，代码就不放了。

---

