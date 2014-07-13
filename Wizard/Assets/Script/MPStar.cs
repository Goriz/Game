﻿using UnityEngine;
using System.Collections;

public class MPStar : MonoBehaviour {

	public int mpspeed = 2;

	private AudioSource success;
	private AudioSource badSound;

	private int mp = 15;
	private int rand = 1;
	private GameObject mpstar1;
	private GameObject mpstar2;
	private GameObject mpstar3;
	private GameObject mpstar4;
	private GameObject mpstar5;
	private GameObject mpstar6;
	private GameObject mpstar7;
	private GameObject mpstar8;
	private GameObject mpstar9;
	private GameObject mpstar10;

	private GameObject upButton;
	private GameObject downButton;
	private GameObject leftButton;
	private GameObject rightButton;



	void Start(){
		AudioSource[] audioSources = GetComponents<AudioSource>();
		success = audioSources[0];
		badSound = audioSources[1];

		mpstar1 = GameObject.Find("MPStar1");
		mpstar2 = GameObject.Find("MPStar2");
		mpstar3 = GameObject.Find("MPStar3");
		mpstar4 = GameObject.Find("MPStar4");
		mpstar5 = GameObject.Find("MPStar5");
		mpstar6 = GameObject.Find("MPStar6");
		mpstar7 = GameObject.Find("MPStar7");
		mpstar8 = GameObject.Find("MPStar8");
		mpstar9 = GameObject.Find("MPStar9");
		mpstar10 = GameObject.Find("MPStar10"); 

		upButton = GameObject.Find("/Command/Camera/Anchor/Panel/UpButton/Label");
		downButton = GameObject.Find("/Command/Camera/Anchor/Panel/DownButton/Label");
		leftButton = GameObject.Find("/Command/Camera/Anchor/Panel/LeftButton/Label");
		rightButton = GameObject.Find("/Command/Camera/Anchor/Panel/RightButton/Label");

		RandButton ();

	}


	void Update(){

		if (mp > mpspeed * 10) {
			mp = mpspeed * 10;
				}

	/* **************************** MPStar Controll ***************************** */
		if (mp >= mpspeed * 10) {
			mpstar10.SetActive (true);
		} else mpstar10.SetActive (false);

		if (mp >= mpspeed * 9) {
			mpstar9.SetActive (true);
		} else mpstar9.SetActive (false);

		if (mp >= mpspeed * 8) {
			mpstar8.SetActive (true);
		} else
			mpstar8.SetActive (false);
		if (mp >= mpspeed * 7) {
			mpstar7.SetActive (true);
		} else
			mpstar7.SetActive (false);
		if (mp >= mpspeed * 6) {
			mpstar6.SetActive (true);
		} else
			mpstar6.SetActive (false);
		if (mp >= mpspeed * 5) {
			mpstar5.SetActive (true);
		} else
			mpstar5.SetActive (false);
		if (mp >= mpspeed * 4) {
			mpstar4.SetActive (true);
		} else
			mpstar4.SetActive (false);
		if (mp >= mpspeed * 3) {
			mpstar3.SetActive (true);
		} else
			mpstar3.SetActive (false);
		if (mp >= mpspeed * 2) {
			mpstar2.SetActive (true);
		} else
			mpstar2.SetActive (false);
		if (mp >= mpspeed * 1) {
			mpstar1.SetActive (true);
		} else
			mpstar1.SetActive (false);

		/* **************************************************************** */

	}



	public void Shot(){
		mp = mp - mpspeed;
	}

	void RandButton(){
		rand = Random.Range (1, 5);
		
		switch(rand){
		case 1:
			upButton.SetActive(true);
			downButton.SetActive(false);
			leftButton.SetActive(false);
			rightButton.SetActive(false);
			break;
		case 2:
			upButton.SetActive(false);
			downButton.SetActive(true);
			leftButton.SetActive(false);
			rightButton.SetActive(false);

			break;
		case 3:
			upButton.SetActive(false);
			downButton.SetActive(false);
			leftButton.SetActive(true);
			rightButton.SetActive(false);

			break;
		case 4:
			upButton.SetActive(false);
			downButton.SetActive(false);
			leftButton.SetActive(false);
			rightButton.SetActive(true);

			break;
		default:
			break;
		}


	}

	void UpButtonPressed() {
		if (rand == 1) {
			success.PlayOneShot(success.clip);
			mp++;
		} else { 
			mp = mp - mpspeed;
			badSound.PlayOneShot(badSound.clip);
		}

		RandButton ();
	}
	
	void DownButtonPressed() {
		if (rand == 2) {
			success.PlayOneShot(success.clip);
			mp++;
		} else {
			mp = mp - mpspeed;
			badSound.PlayOneShot(badSound.clip);
		}

		RandButton ();
	}
	
	/// <summary>右ボタン押された</summary>
	void RightButtonPressed() {
		if (rand == 4) {
			success.PlayOneShot(success.clip);
			mp++;
		} else { 
			mp = mp - mpspeed;
			badSound.PlayOneShot(badSound.clip);
		}
		
		RandButton ();
	}
	
	/// <summary>左ボタン押された</summary>
	void LeftButtonPressed() {
		if (rand == 3) {
			success.PlayOneShot(success.clip);
			mp++;
		} else { 
			mp = mp - mpspeed;
			badSound.PlayOneShot(badSound.clip);
		}
		
		RandButton ();
	} 

}
