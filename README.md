# �������� ������� ��� ���
## �1 (2.4) �� ������� ������ ��������� ������������ ���������� ��������� ���������
### �����: lcg_crack
��������� ����������� ������� ���������:
	X2 = (X1 * a + c) % m (1)
	X3 = (X2 * a + c) % m (2)
	X4 = (X3 * a + c) % m (3)
���������� � (4), (5) ����� ��������� (1) �� (3) � (2):
	X3 - X2 = ((X2 - X1) * a) % m (4)
	X4 - X2 = ((X3 - X1) * a) % m (5)
����� (4) ���������� �� (X3 - X1), � (5) - �� (X2 - X1),
	(X3 - X2)*(X3 - X1) = ((X2 - X1)*(X3 - X1) * a) % m (5)
	(X4 - X2)*(X2 - X1) = ((X3 - X1)*(X2 - X1) * a) % m (6)
(5) ���������� �� (6):
	(X4 - X2)*(X2 - X1) - (X3 - X2)*(X3 - X1) = 0 % m
����� �������, m - ����� ��������� ������� �����: 
	(X4 - X2)*(X2 - X1) - (X3 - X2)*(X3 - X1)
����� ��������� ��� �������� �����, ���������� ������, �.�. ��������:
	- �� ����� ���� ������ ����������� ����� � ������������������
	- �� ����� ���� ������ ������������� m
����� ���� ��������� a � c ������� �������, ��� ���, ���:
	0 < a < m;
	0 <= c < m;
(�� ������� ����������)
�� ����� ������� ���������� ������� ���������� �������� ��������� ��,
� ������� c � m ������� ������� (���� �� �������, ��� �������
��������� ����������� � �������������� m, �.�. ���������� ������
����� ���� ����� ���������� � ��� ������). ������ ������� �����
�������� ���������, ������ ���� ��������� ������������������ ����������
��� ������� ������ ����������, ������ �����, ��� ��� ����� ������ ��������
�����������.

## �2 (2.9) ������ �� ���������-������������ �����
� ������ ������ � ���������� �� �����, � ����� ���� ��������� �������
(�����������, ��� ��������� ������ matlab-�, ��� ������, ������� � C++
����). ������ ��������� �������: ��������� ������ ��� matlab-�, � ����
�������� ��������� ��� ���������� (���������� �������).
������ �� ����� ��������� ����� ��������� ���������-������������
������� �������� � ������� ������� �� ���� ���������:

