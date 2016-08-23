<GameFile>
  <PropertyGroup Name="Enemy" Type="Node" ID="f25fbf63-12d8-4548-9e28-b38b178bd25b" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Node" Tag="1298" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image" ActionTag="672880567" VisibleForFrame="False" Tag="1299" IconVisible="False" LeftMargin="-206.0000" RightMargin="-206.0000" TopMargin="-304.0000" LeftEage="99" RightEage="99" TopEage="99" BottomEage="99" Scale9OriginX="99" Scale9OriginY="99" Scale9Width="214" Scale9Height="106" ctype="ImageViewObjectData">
            <Size X="412.0000" Y="304.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="MarkedSubImage" Path="Images/Monster/s_dragon_green.png" Plist="Csis/Monsters.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="HP" ActionTag="-1190588495" Tag="1300" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-120.0000" RightMargin="-120.0000" TopMargin="-20.0000" TouchEnable="True" ClipAble="False" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="240.0000" Y="20.0000" />
            <Children>
              <AbstractNodeData Name="Bar" ActionTag="713182293" Tag="1301" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" ProgressInfo="100" ctype="LoadingBarObjectData">
                <Size X="240.0000" Y="20.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="120.0000" Y="10.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="68" B="0" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="1.0000" Y="1.0000" />
                <ImageFileData Type="Default" Path="Default/LoadingBarFile.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Name" ActionTag="-417735076" Tag="1302" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="21.0000" RightMargin="21.0000" TopMargin="-4.5000" BottomMargin="-4.5000" FontSize="25" LabelText="グリーンドラゴン" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ShadowEnabled="True" ctype="TextObjectData">
                <Size X="198.0000" Y="29.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="120.0000" Y="10.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="0" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.8250" Y="1.4500" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="68" G="68" B="68" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="APLabel" ActionTag="-52179430" Tag="1304" IconVisible="False" LeftMargin="-44.5000" RightMargin="-44.5000" TopMargin="30.5000" BottomMargin="-59.5000" FontSize="25" LabelText="[AP:1/4]" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="89.0000" Y="29.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="-45.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="136" B="0" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="AP_1" ActionTag="-1683425644" Tag="1305" IconVisible="False" LeftMargin="-60.0000" RightMargin="30.0000" BottomMargin="-30.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="30.0000" Y="30.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="-45.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill_off.png" Plist="Csis/UIParts.plist" />
            <PressedFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <NormalFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="AP_2" ActionTag="367344727" Tag="1306" IconVisible="False" LeftMargin="-30.0000" BottomMargin="-30.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="30.0000" Y="30.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="-15.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill_off.png" Plist="Csis/UIParts.plist" />
            <PressedFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <NormalFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="AP_3" ActionTag="-1747307084" Tag="1307" IconVisible="False" RightMargin="-30.0000" BottomMargin="-30.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="30.0000" Y="30.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="15.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill_off.png" Plist="Csis/UIParts.plist" />
            <PressedFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <NormalFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="AP_4" ActionTag="1807647966" Tag="1308" IconVisible="False" LeftMargin="30.0000" RightMargin="-60.0000" BottomMargin="-30.0000" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="30.0000" Y="30.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position X="45.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill_off.png" Plist="Csis/UIParts.plist" />
            <PressedFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <NormalFileData Type="MarkedSubImage" Path="Images/UIParts/icon_skill.png" Plist="Csis/UIParts.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>