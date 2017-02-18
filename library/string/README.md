## functions and classes for string manipulation

### Prefix function (prefixFunction.cpp)

`vector<int> prefixFunction(string s)`
 - KMP �˰��򿡼� ����ϴ� pattern�� partial matching ������ ���Ѵ�.

`vector<int> prefixFunction(string s, int start)`
 - prefixFunction()�� �����ϳ� s�� start ������ suffix�� ���ؼ��� ����Ѥ���.

`pair<int,int> checkRepeatedString(const vector<int>& prefix, int len)`
 - input : prefix - prefixFunction() ���� ���
 - input : len - �տ������� len ���̱������� �ݺ��� �ִ��� Ȯ���Ѵ�.
 - return : �ݺ� ���ڿ��� �ƴϸ� (-1, -1)��, �ݺ� ���ڿ��̸� (�ݺ� ����, �ݺ� ����)�� ��ȯ�Ѵ�.
 - ���ڿ��� ���� prefixFunction()�� ������ ������� ���� ���ڿ� s�� �տ������� len ���̱����� �ݺ� ���ڿ����� Ȯ���Ѵ�.
 - �ݺ��Ǵ� ������ �߰ߵǸ� (�ݺ� ����, �ݺ� ����) ���� ��ȯ�Ѵ�.

`pair<int,int> checkRepeatedString(const vector<int>& prefix)`
 - input : prefix - prefixFunction() ���� ���
 - return : �ݺ� ���ڿ��� �ƴϸ� (-1, -1)��, �ݺ� ���ڿ��̸� (�ݺ� ����, �ݺ� ����)�� ��ȯ�Ѵ�.
 - ���ڿ��� ���� prefixFunction()�� ������ ������� ���� ���ڿ� s ��ü�� �ݺ� ���ڿ����� Ȯ���Ѵ�.
 - �ݺ��Ǵ� ������ �߰ߵǸ� (�ݺ� ����, �ݺ� ����) ���� ��ȯ�Ѵ�.

`pair<int, int> getMaxRepeatedPrefixString(const vector<int>& prefix)`
 - input : prefix - prefixFunction() ���� ���
 - return : �ݺ� ���ڿ��� ������ (-1, -1)��, ������ ����� �ݺ� ���ڿ��� (�ݺ� ����, �ݺ� ����)�� ��ȯ�Ѵ�.
 - ���ڿ��� ���� prefixFunction()�� ������ ������� �տ��� ���� �ݺ� ���ڿ��� ������ �ִ� ũ�⸦ ã�´�.
 - �ݺ��Ǵ� ������ �߰ߵǸ� (�ݺ� ����, �ݺ� ����) ���� ��ȯ�Ѵ�.

`pair<int, pair<int, int>> getMaxRepeatedSubstring(string s)`
 - input : s - �Է� ���ڿ� 
 - return : �ݺ� ���ڿ��� ������ (-1, (-1, -1))��, ������ ����� �ݺ� ���ڿ��� (��ġ, (�ݺ� ����, �ݺ� ����))�� ��ȯ�Ѵ�.
 - ���ڿ� s�� ��� substring �߿��� �ݺ� ���ڿ��� ������ �ִ� ũ�⸦ ã�´�.
 - �ݺ��Ǵ� ������ �߰ߵǸ� (��ġ, (�ݺ� ����, �ݺ� ����)) ���� ��ȯ�Ѵ�.

`vector<int> kmp(string s, string p)`
 - input : s - �Է� ���ڿ� 
 - input : p - ã�� ����
 - return : ������ �߰ߵ� ��� ��ġ�� ��ȯ�Ѵ�.
 - KMP �˰����� ���ؼ� ���ڿ� s���� ���� p�� ��� ��ġ�� ã�´�.

`vector<int> kmp(string s, string p, const vector<int>& prefix)`
 - input : s - �Է� ���ڿ� 
 - input : p - ã�� ����
 - input : prefix - p�� prefix function ���� ���
 - return : ������ �߰ߵ� ��� ��ġ�� ��ȯ�Ѵ�.
 - KMP �˰����� ���ؼ� ���ڿ� s���� ���� p�� ��� ��ġ�� ã�´�.


### Suffix Array (suffixArray.cpp)

`template <typename T> vector<int> makeSuffixArray(T s, int n)`
 - ���̰� n�� ���ڿ� s���� suffix array�� �����Ѵ�.
 - �� �Լ��� �ð����⵵�� O(N (logN)^2) �̴�.

`template <typename T> vector<int> makeSuffixArrayFast(T s, int n)`
 - ���̰� n�� ���ڿ� s���� suffix array�� �����Ѵ�.
 - �� �Լ��� �ð����⵵�� O(N logN)����, ������ ���� �ӵ��� �����Ѵ�.
   suffixArray_notUsed.cpp�� O(N) �˰����� �����Ǿ�������, ������ �� �Լ��� ���� ���� ���̰� ���� �ʴ´�.
   
`template <typename T> int commonPrefix(T s, int n, int i, int j)`
 - ���ڿ� s���� i��° suffix�� j��° suffix ������ LCP�� ���Ѵ�.

`template <typename T> vector<int> getAllCommonPrefix(const vector<int>& suffixArray, T s, int n)`
 - ��� suffix array ���뿡 ���� LCP�� �Ѳ����� ���Ѵ�. (Kasai algorithm)
 - �ð� ���⵵�� O(N)����, ������ ������ LCP�� ���Ѵ�.

`long long countSubstrings(const vector<int>& suffixArray, T s, int n)`
 - Suffix array�κ��� ��� substring�� ������ ���Ѵ�.
 - �ð� ���⵵�� O(N^2)��, ���� ���� ������ �ƴϴ�.

`template <typename T> long long countSubstringsFast(const vector<int>& suffixArray, T s, int n)`
 - Suffix array�κ��� ��� substring�� ������ ���Ѵ�.
 - ���������� getAllCommonPrefix() �Լ��� ����ϸ� ��ü ���� �ð��� O(N)�̴�.


### ���ڿ� �ڸ��� (split.cpp)

`vector<string> split(string s, char c)`
 - Java�� �ٸ� ���� ���ڿ��� Ư�� delimitor�� �������ִ� ��ɵ��� �����Ǵµ�, C++���� ��� �����ϰ� ����� �� �ִ�.
 - ����� �ſ� �����ؼ� ���ڿ� s�� ���� c�� ���б�ȣ�� ����ؼ� �߶��ش�.

`vector<pair<int,int>> split2(string s, char c)`
 - split() �Լ��� �����ϳ�, ���ڿ� ��ü�� �����ϴ� ���� �ƴ϶� �� substring�� ���� s������ (��ġ, ����)�� �����Ѵ�.
