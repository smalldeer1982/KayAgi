# 题目信息

# Minimize The Integer

## 题目描述

You are given a huge integer $ a $ consisting of $ n $ digits ( $ n $ is between $ 1 $ and $ 3 \cdot 10^5 $ , inclusive). It may contain leading zeros.

You can swap two digits on adjacent (neighboring) positions if the swapping digits are of different parity (that is, they have different remainders when divided by $ 2 $ ).

For example, if $ a = 032867235 $ you can get the following integers in a single operation:

- $ 302867235 $ if you swap the first and the second digits;
- $ 023867235 $ if you swap the second and the third digits;
- $ 032876235 $ if you swap the fifth and the sixth digits;
- $ 032862735 $ if you swap the sixth and the seventh digits;
- $ 032867325 $ if you swap the seventh and the eighth digits.

Note, that you can't swap digits on positions $ 2 $ and $ 4 $ because the positions are not adjacent. Also, you can't swap digits on positions $ 3 $ and $ 4 $ because the digits have the same parity.

You can perform any number (possibly, zero) of such operations.

Find the minimum integer you can obtain.

Note that the resulting integer also may contain leading zeros.

## 说明/提示

In the first test case, you can perform the following sequence of operations (the pair of swapped digits is highlighted): $ 0 \underline{\textbf{70}} 9 \rightarrow 0079 $ .

In the second test case, the initial integer is optimal.

In the third test case you can perform the following sequence of operations: $ 246 \underline{\textbf{43}} 2 \rightarrow 24 \underline{\textbf{63}}42 \rightarrow 2 \underline{\textbf{43}} 642 \rightarrow 234642 $ .

## 样例 #1

### 输入

```
3
0709
1337
246432
```

### 输出

```
0079
1337
234642
```

# AI分析结果

### 题目翻译
## 最小化整数

### 题目描述
给定一个由 $n$ 位数字组成的大整数 $a$（$n$ 的范围是 $1$ 到 $3 \cdot 10^5$，包含边界），它可能包含前导零。

如果相邻位置的两个数字奇偶性不同（即它们除以 $2$ 的余数不同），则可以交换这两个相邻的数字。

例如，如果 $a = 032867235$，你可以通过一次操作得到以下整数：
- 若交换第一位和第二位数字，得到 $302867235$；
- 若交换第二位和第三位数字，得到 $023867235$；
- 若交换第五位和第六位数字，得到 $032876235$；
- 若交换第六位和第七位数字，得到 $032862735$；
- 若交换第七位和第八位数字，得到 $032867325$。

注意，不能交换位置 $2$ 和 $4$ 的数字，因为这两个位置不相邻。同时，也不能交换位置 $3$ 和 $4$ 的数字，因为这两个数字奇偶性相同。

你可以执行任意次数（可能为零次）这样的操作。

找出你能得到的最小整数。

注意，得到的整数也可能包含前导零。

### 说明/提示
在第一个测试用例中，你可以执行以下操作序列（交换的数字对用下划线和粗体标记）：$0 \underline{\textbf{70}} 9 \rightarrow 0079$。

在第二个测试用例中，初始整数就是最优的。

在第三个测试用例中，你可以执行以下操作序列：$246 \underline{\textbf{43}} 2 \rightarrow 24 \underline{\textbf{63}}42 \rightarrow 2 \underline{\textbf{43}} 642 \rightarrow 234642$。

### 样例 #1
#### 输入
```
3
0709
1337
246432
```
#### 输出
```
0079
1337
234642
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心算法。由于相邻奇偶性不同的数字才能交换，所以奇数之间、偶数之间的相对顺序不会改变。题解的主要步骤是将奇数和偶数分别存储在不同的序列中，然后利用类似归并排序的方法，每次比较两个序列的当前元素，将较小的元素放入结果序列，直到其中一个序列遍历完，再将另一个序列的剩余元素直接添加到结果序列末尾。

### 所选题解
- **御前带刀侍卫（4星）**
    - **关键亮点**：思路清晰，通过图文结合的方式解释了归并的过程，代码实现简洁易懂。
    - **核心代码**：
```cpp
string s;
int a1,b1;
int main(){
    int q;
    scanf("%d",&q);
    while(q--){
        cin>>s;
        string a,b;
        a1=b1=0;
        int len=s.length();
        for(int i=0;i<len;i++){
            if((s[i]-'1')&1)a+=s[i],a1++;
            else b+=s[i],b1++;
        }
        a+=120;
        b+=120;
        for(int i=0,j=0;i<=a1&&j<=b1;){
            if(a[i]<b[j]){
                if(a[i]>='0'&&a[i]<='9')
                    printf("%c",a[i]);
                i++;
            }
            else{
                if(b[j]>='0'&&b[j]<='9')
                    printf("%c",b[j]);
                j++;
            }
        }
        printf("\n");
    }
    return 0;
}
```
核心实现思想：先将输入的字符串按奇偶性拆分为两个字符串 `a` 和 `b`，然后在字符串末尾添加标记，方便归并操作。通过比较 `a` 和 `b` 的当前元素，将较小的元素输出，直到两个字符串都遍历完。

- **Mo_xue（4星）**
    - **关键亮点**：详细地阐述了思考过程，通过具体例子解释归并排序的思想，代码结构清晰。
    - **核心代码**：
```cpp
const int N = 3 * 1e5 + 5;
int n;
string s;
int js[N], os[N], ans[N], l1, l2;
void merge_sort() {
    int i = 1, j = 1, k = 0;
    while (i <= l1 && j <= l2)
        if (js[i] < os[j]) ans[++k] = js[i++];
        else ans[++k] = os[j++];
    while (i <= l1) ans[++k] = js[i++];
    while (j <= l2) ans[++k] = os[j++];
    for (int i = 1; i <= k; i++)
        cout << ans[i];
    cout << endl;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        cin >> s;
        l1 = 0;
        l2 = 0;
        for (int i = 0; i < s.size(); i++) {
            int a = s[i] - '0';
            if (a % 2 != 0) js[++l1] = a;
            else os[++l2] = a;
        }
        merge_sort();
    }
    return 0;
}
```
核心实现思想：将输入字符串中的奇数和偶数分别存储在数组 `js` 和 `os` 中，然后调用 `merge_sort` 函数进行归并操作，将较小的元素依次放入 `ans` 数组，最后输出 `ans` 数组。

- **Weakest_Konjac（4星）**
    - **关键亮点**：对操作规则进行了详细分析，明确指出问题可转化为归并排序中的归并操作，代码简洁高效。
    - **核心代码**：
```cpp
const int N=3e5+5;
string a,ans;
int T,n,num1[N],num2[N],cnt1,cnt2;
int main(){
    cin>>T;
    while (T--){
        cin>>a,n=a.length(),cnt1=cnt2=0,ans="";
        for (register int i=0;i<n;++i)
            a[i]&1?num1[++cnt1]=a[i]:num2[++cnt2]=a[i];
        int pos1=1,pos2=1;
        while (pos1<=cnt1&&pos2<=cnt2) num1[pos1]<num2[pos2]?ans+=num1[pos1++]:ans+=num2[pos2++];
        for (register int i=pos1;i<=cnt1;++i) ans+=num1[i];
        for (register int i=pos2;i<=cnt2;++i) ans+=num2[i];
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：将输入字符串中的奇数和偶数分别存储在数组 `num1` 和 `num2` 中，然后使用双指针比较 `num1` 和 `num2` 的当前元素，将较小的元素添加到结果字符串 `ans` 中，最后输出 `ans`。

### 最优关键思路或技巧
- **贪心策略**：利用相邻奇偶性不同的数字才能交换这一规则，确定奇数和偶数内部相对顺序不变，通过归并的方式将两个序列合并成最小的序列。
- **归并思想**：使用双指针分别遍历奇数序列和偶数序列，每次选择较小的元素放入结果序列，保证结果序列字典序最小。

### 拓展思路
同类型题目可能会改变操作规则，例如规定相邻数字满足某种特定关系才能交换，或者改变数字的范围和性质。解题的关键仍然是分析操作对数字相对顺序的影响，然后利用贪心和归并的思想进行求解。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的应用。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：经典的贪心问题，通过排序来实现最优解。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心算法的典型应用，根据单位价值进行排序。

### 个人心得
- **Mo_xue**：通过对题目的分析，发现奇偶性相同的数字相对位置不变这一关键性质，从而想到用归并排序的思想解决问题。这启示我们在解题时要仔细分析题目条件，找出隐藏的规律。

---
处理用时：59.79秒