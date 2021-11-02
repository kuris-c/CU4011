//This is built using the new Unity Input Manager

//Needed Items
//Reference Input Manager
//Reference Camera Manager

private void HandleMovement()
    {
        GetComponent<Rigidbody>().velocity = new Vector3(slideSpeed, 0, movementSpeed);

        //Left Slide
        playerControls.Movement.Left.performed += i => leftMovement = true;

        if (leftMovement && playerLocked == false && transform.position.y < 7.1f)
        {
            slideSpeed = -12;
            StartCoroutine(StopMovement());
            leftMovement = false;
            laneNumber -= 3;
            playerLocked = true;

        }

        //Right Slide
        playerControls.Movement.Right.performed += i => rightMovement = true;

        if (rightMovement && playerLocked == false && transform.position.y < 7.1f)
        {
            slideSpeed = 12;
            StartCoroutine(StopMovement());
            rightMovement = false;
            laneNumber += 3;
            playerLocked = true;
        }

        //Falling off Edge
        if (laneNumber > 3 || laneNumber < -3)
        {
            if (transform.position.y > -10.1f)
            {
                playerLocked = true;
                jumpSpeed = 30;
                GetComponent<Rigidbody>().AddForce(Physics.gravity * jumpSpeed);
            }
            else
            {
                SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
            }
        }

        //Accelerate
        playerControls.Movement.Forward.performed += i => forwardMovement = true;

        if (forwardMovement)
        {
            movementSpeed += 2;
            StartCoroutine(AccelerationChange());
        }

        playerControls.Movement.Back.performed += i => backMovement = true;

        if (backMovement)
        {
            movementSpeed -= 2;
            StartCoroutine(AccelerationChange());
        }

        //Jumping
        playerControls.Movement.Jump.performed += i => jumpMovement = true;

        if (jumpMovement && playerLocked == false && jumpsPerformed == 0)
        {
            jumpSpeed = 8;
            GetComponent<Rigidbody>().AddForce(new Vector3(0, jumpSpeed, 0), ForceMode.Impulse);
            StartCoroutine(StopJumping());
        }

        //Falling
        if (fallingMovement && playerLocked == true)
        {
            playerLocked = true;
            jumpSpeed = 30;
            if (transform.position.y > 1.2f)
            {
                GetComponent<Rigidbody>().AddForce(Physics.gravity * jumpSpeed);
            }
            else
            {
                jumpsPerformed = 0;
                fallingMovement = false;
                playerLocked = false;
            }
        }
    }

    IEnumerator StopMovement()
    {
        yield return new WaitForSeconds(0.25f);
        slideSpeed = 0;
        playerLocked = false;
    }

    IEnumerator AccelerationChange()
    {
        yield return new WaitForSeconds(0.25f);
        forwardMovement = false;
        backMovement = false;
    }

    IEnumerator StopJumping()
    {
        yield return new WaitForSeconds(0.4f);
        playerLocked = true;
        slideSpeed = 0;
        jumpSpeed = 0;
        fallingMovement = true;
        jumpMovement = false;
        jumpsPerformed = 1;
    }
}
