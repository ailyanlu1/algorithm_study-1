## functions and classes for string manipulation

### �Ҽ����� �⺻ �Լ� (prefixFunction.cpp)

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


### ���ڿ� �ڸ��� (split.cpp)

`vector<string> split(string s, char c)`
 - Java�� �ٸ� ���� ���ڿ��� Ư�� delimitor�� �������ִ� ��ɵ��� �����Ǵµ�, C++���� ��� �����ϰ� ����� �� �ִ�.
 - ����� �ſ� �����ؼ� ���ڿ� s�� ���� c�� ���б�ȣ�� ����ؼ� �߶��ش�.

`vector<pair<int,int>> split2(string s, char c)`
 - split() �Լ��� �����ϳ�, ���ڿ� ��ü�� �����ϴ� ���� �ƴ϶� �� substring�� ���� s������ (��ġ, ����)�� �����Ѵ�..
