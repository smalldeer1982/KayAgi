# 题目信息

# Task On The Board

## 题目描述

Polycarp wrote on the board a string $ s $ containing only lowercase Latin letters ('a'-'z'). This string is known for you and given in the input.

After that, he erased some letters from the string $ s $ , and he rewrote the remaining letters in any order. As a result, he got some new string $ t $ . You have to find it with some additional information.

Suppose that the string $ t $ has length $ m $ and the characters are numbered from left to right from $ 1 $ to $ m $ . You are given a sequence of $ m $ integers: $ b_1, b_2, \ldots, b_m $ , where $ b_i $ is the sum of the distances $ |i-j| $ from the index $ i $ to all such indices $ j $ that $ t_j > t_i $ (consider that 'a'&lt;'b'&lt;...&lt;'z'). In other words, to calculate $ b_i $ , Polycarp finds all such indices $ j $ that the index $ j $ contains a letter that is later in the alphabet than $ t_i $ and sums all the values $ |i-j| $ .

For example, if $ t $ = "abzb", then:

- since $ t_1 $ ='a', all other indices contain letters which are later in the alphabet, that is: $ b_1=|1-2|+|1-3|+|1-4|=1+2+3=6 $ ;
- since $ t_2 $ ='b', only the index $ j=3 $ contains the letter, which is later in the alphabet, that is: $ b_2=|2-3|=1 $ ;
- since $ t_3 $ ='z', then there are no indexes $ j $ such that $ t_j>t_i $ , thus $ b_3=0 $ ;
- since $ t_4 $ ='b', only the index $ j=3 $ contains the letter, which is later in the alphabet, that is: $ b_4=|4-3|=1 $ .

Thus, if $ t $ = "abzb", then $ b=[6,1,0,1] $ .

Given the string $ s $ and the array $ b $ , find any possible string $ t $ for which the following two requirements are fulfilled simultaneously:

- $ t $ is obtained from $ s $ by erasing some letters (possibly zero) and then writing the rest in any order;
- the array, constructed from the string $ t $ according to the rules above, equals to the array $ b $ specified in the input data.

## 说明/提示

In the first test case, such strings $ t $ are suitable: "aac', "aab".

In the second test case, such trings $ t $ are suitable: "a", "b", "c".

In the third test case, only the string $ t $ equals to "aba" is suitable, but the character 'b' can be from the second or third position.

## 样例 #1

### 输入

```
4
abac
3
2 1 0
abc
1
0
abba
3
1 0 1
ecoosdcefr
10
38 13 24 14 11 5 3 24 17 0```

### 输出

```
aac
b
aba
codeforces```

# AI分析结果

### 题目中文重写
# 黑板上的任务

## 题目描述
Polycarp 在黑板上写了一个仅包含小写拉丁字母（'a'-'z'）的字符串 $s$。这个字符串是已知的，会在输入中给出。

之后，他从字符串 $s$ 中擦除了一些字母，然后将剩余的字母以任意顺序重新排列，得到了一个新的字符串 $t$。你需要根据一些额外信息找出这个字符串 $t$。

假设字符串 $t$ 的长度为 $m$，字符从左到右依次编号为 $1$ 到 $m$。给定一个长度为 $m$ 的整数序列：$b_1, b_2, \ldots, b_m$，其中 $b_i$ 是从索引 $i$ 到所有满足 $t_j > t_i$ 的索引 $j$ 的距离 $|i - j|$ 之和（假设 'a' < 'b' < ... < 'z'）。换句话说，为了计算 $b_i$，Polycarp 会找出所有满足索引 $j$ 处的字母在字母表中比 $t_i$ 靠后的索引 $j$，并将所有的 $|i - j|$ 值相加。

例如，如果 $t$ = "abzb"，那么：
- 因为 $t_1$ = 'a'，所有其他索引处的字母在字母表中都比它靠后，即：$b_1 = |1 - 2| + |1 - 3| + |1 - 4| = 1 + 2 + 3 = 6$；
- 因为 $t_2$ = 'b'，只有索引 $j = 3$ 处的字母在字母表中比它靠后，即：$b_2 = |2 - 3| = 1$；
- 因为 $t_3$ = 'z'，不存在满足 $t_j > t_i$ 的索引 $j$，所以 $b_3 = 0$；
- 因为 $t_4$ = 'b'，只有索引 $j = 3$ 处的字母在字母表中比它靠后，即：$b_4 = |4 - 3| = 1$。

因此，如果 $t$ = "abzb"，那么 $b = [6, 1, 0, 1]$。

给定字符串 $s$ 和数组 $b$，找出任意一个可能的字符串 $t$，同时满足以下两个条件：
- $t$ 是通过从 $s$ 中擦除一些字母（可能为零个），然后将剩余的字母以任意顺序排列得到的；
- 根据上述规则从字符串 $t$ 构造的数组等于输入数据中指定的数组 $b$。

## 说明/提示
在第一个测试用例中，合适的字符串 $t$ 有："aac"、"aab"。

在第二个测试用例中，合适的字符串 $t$ 有："a"、"b"、"c"。

在第三个测试用例中，只有字符串 $t$ 等于 "aba" 是合适的，但字符 'b' 可以在第二个或第三个位置。

## 样例 #1
### 输入
```
4
abac
3
2 1 0
abc
1
0
abba
3
1 0 1
ecoosdcefr
10
38 13 24 14 11 5 3 24 17 0
```
### 输出
```
aac
b
aba
codeforces
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是利用“当某个位置的 $b$ 值为 $0$ 时，该位置的字母是当前最大的”这一特性，从大到小依次确定字符串 $t$ 中的字符。具体实现上，各题解会先统计原字符串中每个字符的出现次数，然后不断找出 $b$ 值为 $0$ 的位置，选择合适的字符填充这些位置，并更新剩余位置的 $b$ 值，直到所有位置都被确定。

### 所选题解
- **Eibon（5星）**
    - **关键亮点**：思路清晰，代码结构完整，注释较为详细，通过模拟的方式逐步确定字符串 $t$，对边界情况（如 $b[i]$ 均为零的情况）有明确处理。
- **pocafup（4星）**
    - **关键亮点**：使用队列来管理 $b$ 值为 $0$ 的位置，代码简洁，利用 `unordered_map` 统计字符出现次数，并且采用了 $O(1)$ 清空 `unordered_map` 的技巧。
- **Eazin_star（4星）**
    - **关键亮点**：代码逻辑清晰，使用队列和 `map` 分别记录 $0$ 位置和字符出现次数，通过不断更新 $b$ 值和队列，逐步确定字符串。

### 重点代码
#### Eibon 的核心代码
```cpp
bool check()
{
    for(int k=1;k<=m;k++){
        if(b[k]){
            return 1;
        }
    }
    return 0;
}
signed main()
{
    scanf("%lld",&T);
    while(T--){
        cnt=VIP=0;
        memset(ans,0,sizeof ans);
        memset(num,0,sizeof num);
        scanf("%s%lld",s+1,&m);
        n=strlen(s+1);
        for(int i=1;i<=n;i++){
            num[s[i]-'a'+1]++;
            if(num[s[i]-'a'+1]==1){
                a[++cnt]=s[i]-'a'+1;
            }
        }
        sort(a+1,a+cnt+1);
        for(int i=1;i<=m;i++){
            scanf("%lld",&b[i]);
        }
        while(check()){
            VIP++;v=0;
            for(int i=1;i<=m;i++){
                if(!b[i]&&!ans[i]){
                    v++;
                }
            }
            while(1){
                if(num[a[cnt-VIP+1]]<v){
                    VIP++;
                }
                else{
                    break;
                }
            }
            for(int i=1;i<=m;i++){
                if(!b[i]&&!ans[i]){
                    ans[i]=a[cnt-VIP+1];
                }
            }
            for(int i=1;i<=m;i++){
                if(ans[i]==a[cnt-VIP+1]){
                    for(int j=1;j<=m;j++){
                        if(b[j]){
                            b[j]-=abs(i-j);
                        }
                    }
                }
            }
        }
        VIP++;v=0;
        for(int i=1;i<=m;i++){
            if(!b[i]&&!ans[i]){
                v++;
            }
        }
        while(1){
            if(num[a[cnt-VIP+1]]<v){
                VIP++;
            }
            else{
                break;
            }
        }
        for(int i=1;i<=m;i++){
            if(!b[i]&&!ans[i]){
                ans[i]=a[cnt-VIP+1];
            }
        }
        for(int i=1;i<=m;i++){
            char c=(char)ans[i]+'a'-1;
            cout<<c;
        }
        printf("\n");
    }
    return 0;
}
```
**核心实现思想**：先统计字符出现次数并排序，然后不断检查是否还有非零的 $b$ 值。每次找到 $b$ 值为 $0$ 且未确定字符的位置，选择合适的字符填充，再更新剩余位置的 $b$ 值，直到所有位置都被确定。

#### pocafup 的核心代码
```cpp
signed main(){
    cin >> t;
    while(t--){
        cin >> s >> n;
        unordered_map<char,int> tmp;
        memset(vis,0,sizeof(vis));
        swap(tmp,mp);
        for (int i : s) mp[i-96]++;
        for (int i=0;i<n;i++) {
            cin >> pos[i];
            if (pos[i]==0) q2.push(i),vis[i] = true;
        }
        swap(q,q2);
        int curr = 26;
        while(mp[curr]<q.size()) curr--;
        while(!q.empty()){
            int qf = q.front(); q.pop();
            for (int i=0;i<n;i++) {
                if (vis[i]) continue;
                pos[i]-=abs(qf-i);
                if (pos[i]==0) q2.push(i),vis[i] = true;
            }
            ans[qf] = curr;
            if (q.empty()) {
                swap(q,q2);
                curr--;
                while(mp[curr]<q.size() && curr!=0) curr--;
            }
        }
        for (int i=0;i<n;i++) cout << char(ans[i]+96);
        cout << endl;
    }
}
```
**核心实现思想**：使用队列管理 $b$ 值为 $0$ 的位置，利用 `unordered_map` 统计字符出现次数。每次从队列中取出一个位置，更新其他位置的 $b$ 值，若有新的 $b$ 值为 $0$ 的位置则加入队列，直到队列为空。

#### Eazin_star 的核心代码
```cpp
int main() {
    scanf("%d", &t);
    while (t--) {
        cin >> s;
        scanf("%d", &m);
        memset(vis, 0, sizeof vis);
        mp.clear();
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            mp[c]++;
        }
        for (int i = 1; i <= m; i++) {
            scanf("%d", &a[i]);
            if (!a[i]) qq.push(i), vis[i] = 1;
        }
        swap(q, qq);
        char cur = 'z';
        while (mp[cur] < q.size()) cur--;
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            for (int i = 1; i <= m; i++) {
                if (vis[i]) continue;
                a[i] -= abs(t-i);
                if (!a[i]) qq.push(i), vis[i] = 1;
            }
            ans[t] = cur;
            if (q.empty()) {
                swap(q, qq);
                cur--;
                while (mp[cur] < q.size() && cur != 'a') cur--;
            }
        }
        for (int i = 1; i <= m; i++) cout << ans[i];
        putchar('\n');
    }	
    return 0;
}
```
**核心实现思想**：使用队列和 `map` 分别记录 $0$ 位置和字符出现次数。不断从队列中取出位置，更新其他位置的 $b$ 值，若有新的 $b$ 值为 $0$ 的位置则加入队列，直到队列为空。

### 关键思路或技巧
- 利用“$b$ 值为 $0$ 的位置的字母是当前最大的”这一特性，从大到小依次确定字符。
- 使用队列来管理 $b$ 值为 $0$ 的位置，方便进行后续操作。
- 统计原字符串中每个字符的出现次数，确保选择的字符数量足够。

### 拓展思路
同类型题或类似算法套路通常涉及字符串的构造和条件匹配。例如，给定一些字符串的特征（如字符频率、相邻字符关系等），要求构造出满足这些特征的字符串。解题时可以借鉴本题的思路，从特殊条件入手，逐步确定字符串的各个部分。

### 推荐洛谷题目
- [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)

### 个人心得
- pocafup：赛时想不出，赛后秒解，提醒我们在比赛时要保持冷静，赛后要及时总结。
- Lily_White：不看数据范围把 $n$ 当作 $2\times 10^5$ 导致卡了好久，强调了在解题前要仔细分析数据范围，避免不必要的错误。

---
处理用时：75.17秒