# 题目信息

# [CEOI 2005] Multi-key Sorting

## 题目描述

考虑一个包含行和列的表。列从 $1$ 到 $C$ 编号。为简单起见，表中的项目是由小写字母组成的字符串。  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/z70sexo1.png)  
您将获得对此类表的 Sort($k$) 操作：Sort($k$) 按照列 $k$ 中的值的顺序对表的行进行排序（而列的顺序不会改变）。排序是稳定的，即在第 $k$ 列中具有相等值的行保持其原始顺序。例如，将 Sort($2$) 应用于表 $1$ 会产生表 $2$。  
我们对此类排序操作的序列感兴趣。这些操作依次应用于同一个表。例如，应用序列 Sort($2$)；Sort($1$) 到表 $1$ 产生表 $3$。  
如果两个排序操作序列对于任何表具有相同的效果，则它们被称为等效。例如，Sort($2$)；Sort($2$)；Sort($1$) 等效于 Sort($2$)；Sort($1$)。但是，它不等效于 Sort($1$)；Sort($2$)，因为对表 $1$ 的影响不同。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq C \leq 10^6$，$1 \leq N \leq 3×10^6$，$1 \leq k_i \leq C$。  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2005 的 Multi-key Sorting。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
4 6
1 2 1 2 3 3```

### 输出

```
3
1 2 3```

# AI分析结果

### 算法分类
排序

### 综合分析与结论
题目要求对序列进行多次稳定排序操作，并找到最短的等效排序方法。核心思路是保留每种排序的最后一次操作，因为稳定排序具有幂等性，重复操作不影响结果。所有题解都围绕这一思路展开，通过桶排或记录最后一次出现的位置来实现。

### 所选题解
1. **作者：Gumbo (5星)**
   - **关键亮点**：清晰解释了稳定排序的幂等性，并直接提出保留最后一次排序操作的思路，代码简洁高效。
   - **代码核心**：
     ```cpp
     int lst[1000006];
     int num[3000006];
     int main(){
         int c,n;
         scanf("%d%d",&c,&n);
         int ans=0;
         for(int i=1;i<=n;++i){
             scanf("%d",&num[i]);
             if(lst[num[i]]==0)++ans;
             lst[num[i]]=i;
         }
         printf("%d\n",ans);
         for(int i=1;i<=n;++i)if(lst[num[i]]==i)printf("%d ",num[i]);
         return 0;
     }
     ```
   - **核心思想**：使用 `lst` 数组记录每个数最后一次出现的位置，输入时统计不同数的个数，输出时按最后一次出现的位置输出。

2. **作者：_Evergarden_ (4星)**
   - **关键亮点**：详细解释了题目要求，并通过倒序枚举和标记数组实现，代码结构清晰。
   - **代码核心**：
     ```cpp
     int c, n, a[N], b[N], ans, l[N], cnt;
     int main() {
         cin >> c >> n;
         for(int i = 1; i <= n; ++ i) {
             cin >> a[i];
             b[a[i]] ++;
         }
         for(int i = 1; i <= 1000000; ++ i) {
             if(b[i] != 0) ans++;
         }
         cout << ans << "\n";
         memset(b, 0, sizeof b);
         for(int i = n; i >= 1; -- i) {
             if(!b[a[i]]) {
                 l[++cnt] = a[i];
                 b[a[i]] = 1;
             }
         }
         for(int i = cnt; i >= 1; -- i) {
             cout << l[i] << " ";
         }
         return 0;
     }
     ```
   - **核心思想**：使用 `b` 数组统计每个数的出现次数，倒序枚举时记录每个数最后一次出现的位置，并按顺序输出。

3. **作者：happybob (4星)**
   - **关键亮点**：通过逆序遍历和标记数组实现，代码简洁明了。
   - **代码核心**：
     ```cpp
     bool vis[N];
     int n, a[N], cnt = 0;
     vector<int> ans;
     int main() {
         scanf("%*d%d", &n);
         for (int i = 1; i <= n; i++) {
             scanf("%d", &a[i]);
         }
         for (int i = n; i >= 1; i--) {
             if (!vis[a[i]]) {
                 cnt++;
                 vis[a[i]] = true;
             }
         }
         printf("%d\n", cnt);
         memset(vis, false, sizeof(vis));
         for (int i = n; i >= 1; i--) {
             if (!vis[a[i]]) {
                 ans.push_back(a[i]);
                 vis[a[i]] = true;
             }
         }
         reverse(ans.begin(), ans.end());
         for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
         printf("\n");
         return 0;
     }
     ```
   - **核心思想**：使用 `vis` 数组标记每个数是否出现过，逆序遍历时记录每个数最后一次出现的位置，并按顺序输出。

### 最优关键思路
- **保留最后一次排序操作**：由于稳定排序的幂等性，只需保留每种排序的最后一次操作。
- **倒序枚举**：通过倒序枚举序列，可以方便地记录每个数最后一次出现的位置。
- **标记数组**：使用标记数组记录每个数是否已经出现过，避免重复处理。

### 可拓展之处
- **同类型题**：类似问题可以扩展到多关键字排序、去重等问题。
- **算法套路**：倒序枚举和标记数组的技巧可以应用于需要记录最后一次出现位置的场景。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)

---
处理用时：34.80秒