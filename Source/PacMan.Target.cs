// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class PacManTarget : TargetRules
{
	public PacManTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;


        // Optionnel : Forcer la configuration du build si nécessaire
        bOverrideBuildEnvironment = true;

		ExtraModuleNames.AddRange( new string[] { "PacMan" } );
	}
}
