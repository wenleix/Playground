function [L,U]=lu_nopiv(A)
% LU factorization of an n by n matrix A
% using Gauss elimination without pivoting
% LU_factor.m
% A is factored as A = L*U
% Output:
% L is lower triangular with the main diagonal part = 1s.
% U is upper triangular and is stored in the original mtx A
% and must be zeroed out to get U
% K. Ming Leung, 01/26/03

U = A;
n = size(A, 1);
L=eye(n);
for k=1:n
    if (U(k,k) == 0) Error('Pivoting is needed!'); end
    L(k+1:n,k)=U(k+1:n,k)/U(k,k);
    for j=k+1:n
        U(j,:)=U(j,:)-L(j,k)*U(k,:);
    end
end
 