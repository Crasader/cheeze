<GameFile>
  <PropertyGroup Name="EnemyUnit" Type="Node" ID="f25fbf63-12d8-4548-9e28-b38b178bd25b" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Node" Tag="1298" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Image" ActionTag="672880567" VisibleForFrame="False" Tag="1299" IconVisible="False" LeftMargin="-58.5000" RightMargin="-58.5000" TopMargin="-125.0000" LeftEage="41" RightEage="41" TopEage="31" BottomEage="31" Scale9OriginX="41" Scale9OriginY="31" Scale9Width="35" Scale9Height="63" ctype="ImageViewObjectData">
            <Size X="117.0000" Y="125.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Default" Path="Default/ImageFile.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="BgImage" ActionTag="1782496531" Tag="381" IconVisible="False" LeftMargin="-82.0000" RightMargin="-82.0000" TopMargin="-2.0000" BottomMargin="-40.0000" LeftEage="211" RightEage="211" TopEage="211" BottomEage="211" Scale9OriginX="211" Scale9OriginY="211" Scale9Width="218" Scale9Height="218" ctype="ImageViewObjectData">
            <Size X="164.0000" Y="42.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
            <Position Y="2.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="MarkedSubImage" Path="Images/UIParts/bg_lucent.png" Plist="Csis/UIParts.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="HP" ActionTag="-1190588495" Tag="1300" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="-75.0000" RightMargin="-75.0000" TopMargin="2.5000" BottomMargin="-17.5000" TouchEnable="True" ClipAble="False" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="150.0000" Y="15.0000" />
            <Children>
              <AbstractNodeData Name="Bar" ActionTag="713182293" Tag="1301" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" ProgressInfo="100" ctype="LoadingBarObjectData">
                <Size X="150.0000" Y="15.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="75.0000" Y="7.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="68" B="0" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="1.0000" Y="1.0000" />
                <ImageFileData Type="Default" Path="Default/LoadingBarFile.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Label" ActionTag="2136084513" VisibleForFrame="False" Tag="646" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-211.5000" RightMargin="-211.5000" TopMargin="-40.5000" BottomMargin="-40.5000" LabelText="HP:99999/99999" ctype="TextBMFontObjectData">
                <Size X="573.0000" Y="96.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="75.0000" Y="7.5000" />
                <Scale ScaleX="0.2500" ScaleY="0.2500" />
                <CColor A="255" R="255" G="238" B="136" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="3.8200" Y="6.4000" />
                <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="-10.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="68" G="68" B="68" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Name" ActionTag="1202136412" Tag="644" IconVisible="False" LeftMargin="-116.5000" RightMargin="-116.5000" TopMargin="-38.0000" BottomMargin="-58.0000" LabelText="キラリ" ctype="TextBMFontObjectData">
            <Size X="233.0000" Y="96.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="-10.0000" />
            <Scale ScaleX="0.2500" ScaleY="0.2500" />
            <CColor A="255" R="255" G="238" B="136" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="APLabel" ActionTag="1092017831" Tag="645" IconVisible="False" LeftMargin="-73.5000" RightMargin="-173.5000" TopMargin="-18.0000" BottomMargin="-78.0000" LabelText="[AP:1]" ctype="TextBMFontObjectData">
            <Size X="247.0000" Y="96.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="50.0000" Y="-30.0000" />
            <Scale ScaleX="0.2000" ScaleY="0.2000" />
            <CColor A="255" R="255" G="170" B="68" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="AP_1" ActionTag="-1683425644" Tag="1305" IconVisible="False" LeftMargin="-80.0000" RightMargin="60.0000" TopMargin="19.9993" BottomMargin="-39.9993" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="20.0000" Y="20.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-70.0000" Y="-29.9993" />
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
          <AbstractNodeData Name="AP_2" ActionTag="367344727" Tag="1306" IconVisible="False" LeftMargin="-61.9997" RightMargin="41.9997" TopMargin="19.9994" BottomMargin="-39.9994" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="20.0000" Y="20.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-51.9997" Y="-29.9994" />
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
          <AbstractNodeData Name="AP_3" ActionTag="-1747307084" Tag="1307" IconVisible="False" LeftMargin="-43.9997" RightMargin="23.9997" TopMargin="19.9994" BottomMargin="-39.9994" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="20.0000" Y="20.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-33.9997" Y="-29.9994" />
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
          <AbstractNodeData Name="AP_4" ActionTag="1807647966" Tag="1308" IconVisible="False" LeftMargin="-26.0000" RightMargin="6.0000" TopMargin="19.9993" BottomMargin="-39.9993" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="20.0000" Y="20.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="-16.0000" Y="-29.9993" />
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
          <AbstractNodeData Name="AP_5" ActionTag="1872808169" Tag="1246" IconVisible="False" LeftMargin="-7.9998" RightMargin="-12.0002" TopMargin="19.9993" BottomMargin="-39.9993" TouchEnable="True" FontSize="14" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="50" Scale9Height="58" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="20.0000" Y="20.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="2.0002" Y="-29.9993" />
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