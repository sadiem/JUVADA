//################################################
// <DeadNum.cpp>
// �Q�[����ʒ��A��ɃX�R�A�̏o��(2D)
//------------------------------------------------
// 2013/01/30 ~
//						SekiyamaRumi
//################################################

//================================================
//�C���N���[�h�w�b�_
//================================================
#include "DeadNum.h"

//++++++++++++++++++++++++++++++++++++++++++++++++
//�e�N�X�`��ID�Z�b�g
//--in--------------------------------------------
//�e�N�X�`��ID
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void DEAD_NUM::SetTexID(GLuint TexID)
{
	m_TexID = TexID;
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//���l�Z�b�g
//--in--------------------------------------------
//���S��
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void DEAD_NUM::SetNum(int nDeadNum)
{
	NUM_VIEW::Updata(nDeadNum);
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�e�N�X�`�����
//--in--------------------------------------------
//�����ʒu
//��	(1������)
//����
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void DEAD_NUM::SetVer(int X, int Y, int W, int H)
{
	NUM_VIEW::m_x = X;
	NUM_VIEW::m_y = Y;
	NUM_VIEW::m_num_w = W;
	NUM_VIEW::m_num_h = H;
}
//++++++++++++++++++++++++++++++++++++++++++++++++
//�`��
//--in--------------------------------------------
//���S��
//--out-------------------------------------------
//�Ȃ�
//++++++++++++++++++++++++++++++++++++++++++++++++
void DEAD_NUM::Draw(void)
{
	NUM_VIEW::Draw(m_TexID);
}
//################################################
// End of File
//################################################