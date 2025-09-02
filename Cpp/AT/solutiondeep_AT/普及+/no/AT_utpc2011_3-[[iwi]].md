# 题目信息

# [[iwi]]

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2011/tasks/utpc2011_3

# AI分析结果

### 题目内容
#### 题目描述
给定一个长度不超过15的字符串，要求从中选取一个子序列，使得该子序列的正中间是`iwi`，并且该子序列是对称的。求满足条件的子序列的最大长度。

### 算法分类
枚举、字符串

### 题解分析与结论
本题的核心思路是通过枚举所有可能的子序列，判断其是否满足中间为`iwi`且对称的条件。由于字符串长度不超过15，暴力枚举的复杂度是可接受的。大多数题解采用了位运算来枚举子序列，并通过双指针或直接比较来判断对称性。

### 高星题解推荐

#### 题解作者：Rigel (赞：8)
**星级：4.5**
**关键亮点：**
- 使用DFS进行子序列枚举，代码结构清晰。
- 通过map存储括号的对应关系，简化了对称性判断。
- 时间复杂度为$\mathcal{O}(n2^n)$，在题目限制下完全可行。

**核心代码：**
```cpp
void dfs(int now,int stp,int m){ // 在 n 个字符中选 m 个
	if(stp>m){
		int mid=(m>>1)+1;
		if(t[mid-1]!='i'||t[mid]!='w'||t[mid+1]!='i')return; // 判断字符串正中间是否是 iwi
		for(int i=1;i<=mid-2;i++){ // 判断字符串是否对称
			if(!mp[t[i]]){if(t[i]!=t[m-i+1])return;} // 若当前字符不是括号，判断另一边的字符与其是否一致
			else{if(mp[t[i]]!=t[m-i+1])return;} // 否则，判断另一边的字符是否是当前字符的另一半
		}
		ans=max(ans,m);
		return;
	}
	for(int i=now;i<=n;i++){
		if(vis[i])continue;
		vis[i]=1;
		t[stp]=a[i];
		dfs(i,stp+1,m);
		vis[i]=0;
	}
}
```

#### 题解作者：0x3F (赞：5)
**星级：4**
**关键亮点：**
- 使用位运算枚举子序列，代码简洁高效。
- 通过双指针判断对称性，逻辑清晰。
- 时间复杂度为$\Theta(n2^n)$，适合小规模数据。

**核心代码：**
```cpp
int len(string str) {
	if (str.size() < 3) return -1;
	if (!(str.size()&1)) return -1;
	if (str[str.size()>>1] != 'w') return -1;
	if (str[(str.size()>>1)+1] != 'i') return -1;
	if (str[(str.size()>>1)-1] != 'i') return -1;
	for (int i = 0, j = str.size()-1; i <= j; i++, j--) {
		if (str[i] == 'i' && str[j] == 'i') continue;
		if (str[i] == 'w' && str[j] == 'w') continue;
		if (str[i] == '(' && str[j] == ')') continue;
		if (str[i] == ')' && str[j] == '(') continue;
		if (str[i] == '[' && str[j] == ']') continue;
		if (str[i] == ']' && str[j] == '[') continue;
		if (str[i] == '{' && str[j] == '}') continue;
		if (str[i] == '}' && str[j] == '{') continue;
		return -1;
	}
	return str.size();
}
```

#### 题解作者：Wf_yjqd (赞：1)
**星级：4**
**关键亮点：**
- 使用区间DP解决最长回文子序列问题，时间复杂度为$\operatorname{O}(n^2)$。
- 通过固定中间为`iwi`，简化了问题。
- 代码结构清晰，适合理解DP的应用。

**核心代码：**
```cpp
inline bool check(char x,char y){
    if(x==y)
        return x=='i'||x=='w';
    return x=='('&&y==')'||y=='('&&x==')'||x=='['&&y==']'||y=='['&&x==']'||x=='{'&&y=='}'||y=='{'&&x=='}';
}
int main(){
    memset(dp,0x8f,sizeof(dp));
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i+2<=n;i++)
        if(s[i]=='i'&&s[i+1]=='w'&&s[i+2]=='i')
            dp[i][i+2]=3;
    for(int len=4;len<=n;len++){
        for(int l=1,r;l+len-1<=n;l++){
            r=l+len-1;
            dp[l][r]=max(dp[l+1][r],dp[l][r-1]);
            if(check(s[l],s[r]))
                dp[l][r]=max(dp[l][r],dp[l+1][r-1]+2);
        }
    }
    printf("%d Sherry\n",dp[1][n]);
    return 0;
}
```

### 最优关键思路
1. **位运算枚举子序列**：通过二进制位表示字符的选取情况，简化了子序列的生成过程。
2. **双指针判断对称性**：通过双指针从两端向中间遍历，判断字符是否对称，逻辑清晰且高效。
3. **区间DP优化**：对于更长的字符串，可以使用区间DP来优化求解过程，时间复杂度为$\operatorname{O}(n^2)$。

### 拓展思路
- **类似题目**：可以扩展到更长的字符串，或者要求子序列满足其他对称条件。
- **算法优化**：对于更大规模的数据，可以考虑使用更高效的算法或数据结构进行优化。

### 推荐题目
1. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

---
处理用时：41.40秒