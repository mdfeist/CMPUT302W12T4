/**
 * XBoxInput.h
 * Created By: Devon Waldon
 */

namespace XBoxInput{
	/*
	Menu setups for defining how buttons work for each menu state.
	*/
	int setMenuNormal();
	int setMenuSelect();
	int setMenuCamera();
	int setMenuModel();
	int setMenuSave();

	/*
	Camera adjustment methods. Used in the setMenuCamera menu state.
	*/
	int modifyCameraOffsetX();
	int modifyCameraOffsetY();
	int modifyCameraOffsetZ();

	int increaseFOV();
	int decreaseFOV();

	int increaseAspect();
	int decreaseAspect();

	/*
	Model adjustment methods. Used in the setMenuModel menu state.
	*/
	extern int selectedModel;

	int modifyModelRotationX();
	int modifyModelRotationY();
	int modifyModelRotationZ();

	int modelIncreaseScale();
	int modelDecreaseScale();

	int modelFlipX();
	int modelFlipY();
	int modelFlipZ();

}