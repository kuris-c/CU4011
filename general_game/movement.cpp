//Character Controller
//Hides Cursor For Player During Default Gameplay

        //Cursor.visible = false;

        //Key Commands
        isSprinting = Input.GetKey(KeyCode.LeftShift);
        isCrouching = Input.GetKey(KeyCode.LeftControl);
        if (cController.isGrounded)
        {
            moveDirection.x = walkSpeed * Input.GetAxis("Horizontal");
            moveDirection.z = walkSpeed * Input.GetAxis("Vertical");
            maxJumps = curJumps;
            moveDirection.y = 0;
        }

        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            dealDamage();
        }

        //Jumping Movement + Double Jump + Stamina Loss
        if (Input.GetButton("Jump") && cController.velocity.y == 0 && !isCrouching && !isSprinting)
        {
            if (maxJumps > 0)
            {
                moveDirection.y = jumpHeight;
                maxJumps--;
            }
        }

        //Crouching Movement + Stamina Loss
        if (isCrouching)
        {
            tempCharHeight = crouchHeight;
            moveDirection.x = crouchSpeed * Input.GetAxis("Horizontal");
            moveDirection.z = crouchSpeed * Input.GetAxis("Vertical");
        }

        else if (!isCrouching)
        {
            tempCharHeight = defCharHeight;
        }

        if (tempCharHeight != defCharHeight && crouchLerp < 1)
        {
            crouchLerp += crouchTime;
        }

        else if (tempCharHeight == defCharHeight && crouchLerp > 0)
        {
            crouchLerp -= crouchTime;
        }

        cController.height = Mathf.Lerp(defCharHeight, crouchHeight, crouchLerp);


        //Sprinting Movement + Stamina Loss
        if (cController.isGrounded && isSprinting)
        {
            //    moveDirection = transform.TransformDirection(sprintSpeed * Input.GetAxis("Horizontal"), 0, sprintSpeed * Input.GetAxis("Vertical"));
            moveDirection.x = sprintSpeed * Input.GetAxis("Horizontal");
            moveDirection.z = sprintSpeed * Input.GetAxis("Vertical");
        }

        //Directional Movement
        currentRotation.x += Input.GetAxis("Mouse X") * moveSensitivity;
        currentRotation.x = Mathf.Repeat(currentRotation.x, 360); //Mathf.Lerp
        transform.rotation = Quaternion.Euler(0, currentRotation.x, 0); //Quarternions used to convert

        currentRotation.y -= Input.GetAxis("Mouse Y") * (moveSensitivity * 0.3f);
        currentRotation.y = Mathf.Repeat(currentRotation.y, 360);
        cam.transform.rotation = Quaternion.Euler(currentRotation.y, currentRotation.x, 0); //x,y,z

        moveDirection.y -= gravity * Time.deltaTime;
        cController.Move(transform.TransformDirection(moveDirection) * Time.deltaTime);
